#include "game/game.h"
#include "game/physicsFixedObject.h"
#include "game/physicsObject.h"
#include "game/rigidObject.h"
#include "resource_manager.h"

#include "spdlog/spdlog.h"
#include "yaml-cpp/yaml.h"

#include <ranges>
#include <string>
#include <utility>
#include <vector>

extern YAML::Node config;

void GameProject::Init() {
	spdlog::info("Initializing game");
	this->adapter.Init(this->width, this->height);

	spdlog::info("Loading Texture...");
	YAML::Node textures = config["textures"];
	for (auto &&texture : textures) {
		ResourceManager::LoadTexture(
			(texture["path"]
				 ? texture["path"].as<std::string>()
				 : "./texture/" + texture["id"].as<std::string>() +
					   ".png")
				.c_str(),
			texture["alpha"] ? texture["alpha"].as<bool>() : false,
			texture["id"].as<std::string>());
		spdlog::debug("Loaded texture from file {} as {} (alpha:{})",
					  texture["path"].as<std::string>(),
					  texture["id"].as<std::string>(),
					  texture["alpha"] ? texture["alpha"].as<bool>()
									   : false);
	}

	spdlog::info("Loading Events...");
	InitEvents(&this->events);

	spdlog::info("Loading Objects...");
	this->ChangeState("MainMenu");
	spdlog::info("Game Inited.");
}

void GameProject::ProcessInput(float dt) {
	for (auto [key, event] : keyMap) {
		if (this->adapter.GetKeyState(key)) {
			eventList.push_back(event);
		}
	}
	for (auto event = this->adapter.GetNextMouseEvent();
		 std::get<0>(event) != -1;
		 event = this->adapter.GetNextMouseEvent()) {
		auto [key, state, pos] = event;
		auto [x, y] = pos;
		for (auto [zindex, key] : this->zIndexQueue) {
			auto *gameObject = this->gameObjects[key];
			if (x >= gameObject->GetPosX() &&
				x < gameObject->GetPosX() + gameObject->GetWidth() &&
				y >= gameObject->GetPosY() &&
				y < gameObject->GetPosY() +
						gameObject->GetHeight()) {
				eventList.push_back(gameObject->GetOnClickEvent());
				break;
			}
		}
	}
}

void GameProject::Update(float dt) {
	// spdlog::debug("Updating game, dt: {}s", dt);
	for (auto &[zindex, key] :
		 std::ranges::reverse_view(this->zIndexQueue)) {
		this->gameObjects[key]->Update(dt);
	}
	for (auto gameObjectX = this->gameObjects.begin();
		 gameObjectX != this->gameObjects.end(); ++gameObjectX) {
		if (!gameObjectX->second->IsPhysicsObject()) {
			continue;
		}
		for (auto gameObjectY = std::next(gameObjectX);
			 gameObjectY != this->gameObjects.end(); ++gameObjectY) {
			if (!gameObjectY->second->IsPhysicsObject()) {
				continue;
			}
			if (gameObjectX->second == gameObjectY->second) {
				continue;
			}
			if (CheckCollision(reinterpret_cast<PhysicsObject *>(
								   gameObjectX->second),
							   reinterpret_cast<PhysicsObject *>(
								   gameObjectY->second))) {
				OnCollision(reinterpret_cast<PhysicsObject *>(
								gameObjectX->second),
							reinterpret_cast<PhysicsObject *>(
								gameObjectY->second));
			}
		}
	}
	for (const auto &event : this->eventList) {
		this->events[event]->Process(this, dt);
	}
	eventList.clear();
}

void GameProject::Render() {
	for (auto &[zindex, key] :
		 std::ranges::reverse_view(this->zIndexQueue)) {
		this->gameObjects[key]->Render(&this->adapter);
	}
}

void GameProject::CleanUp() {
	for (auto [key, gameObject] : this->gameObjects) {
		gameObject->RemoveObjectEvents(&this->events);
		delete gameObject;
	}
	this->gameObjects.clear();
	this->zIndexQueue.clear();
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
}

auto createNewGameObject(YAML::Node &object) -> GameObject * {
	GameObject *gameObject;
	if (!object["type"]) {
		object["type"] = "gameObject";
	}
	// TODO(shiyihang): 添加名称至类型的映射
	if (object["type"].as<std::string>() == "staticObject") {
		gameObject = new StaticObject;
	}
	else if (object["type"].as<std::string>() == "physicsObject") {
		gameObject = new PhysicsObject;
	}
	else if (object["type"].as<std::string>() ==
			 "physicsFixedObject") {
		gameObject = new PhysicsFixedObject;
	}
	else if (object["type"].as<std::string>() == "rigidObject") {
		gameObject = new RigidObject;
	}
	else {
		gameObject = new GameObject;
	}

	gameObject->SetObjectByYaml(object);
	return gameObject;
}
void GameProject::ChangeState(GameState newState) {
	spdlog::info("Changing state: {} -> {}", this->gameState,
				 newState);
	this->gameState = std::move(newState);
	for (auto [key, gameObject] : this->gameObjects) {
		gameObject->RemoveObjectEvents(&this->events);
		delete gameObject;
	}
	this->gameObjects.clear();
	this->zIndexQueue.clear();

	YAML::Node stateInfo = config["states"][this->gameState];
	for (auto &&object : stateInfo["objects"]) {
		if (this->gameObjects.contains(
				object["name"].as<std::string>())) {
			spdlog::warn("Duplicate object name: {}; Skipping",
						 object["name"].as<std::string>());
			continue;
		}
		this->gameObjects[object["name"].as<std::string>()] =
			createNewGameObject(object);
		this->gameObjects[object["name"].as<std::string>()]
			->InsertObjectEvents(&this->events);
		this->zIndexQueue.emplace(
			object["zindex"] ? object["zindex"].as<double>() : 0,
			object["name"].as<std::string>());
		spdlog::debug("Loaded object '{}'",
					  object["name"].as<std::string>());
	}

	this->keyMap.clear();
	for (auto &&keyBind : stateInfo["keyMap"]) {
		if (this->adapter.GetKeyCode(
				keyBind["key"].as<std::string>()) == -1) {
			spdlog::warn("Invalid key: {}; Skipping",
						 keyBind["key"].as<std::string>());
			continue;
		}
		if (this->keyMap.contains(this->adapter.GetKeyCode(
				keyBind["key"].as<std::string>()))) {
			spdlog::warn("Duplicate key: {}; Skipping",
						 keyBind["key"].as<std::string>());
			continue;
		}
		this->keyMap[this->adapter.GetKeyCode(
			keyBind["key"].as<std::string>())] =
			keyBind["action"].as<std::string>();
	}

	spdlog::info("State change done.");
}
