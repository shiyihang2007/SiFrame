#include "game/game.h"
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
	for (int i = 0; i < 1024; ++i) {
		if (this->adapter.GetKeyState(i)) {
			this->events[!this->keyMap.contains(i) ? "none"
												   : this->keyMap[i]]
				->Process(this);
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
	for (auto [key, gameObject] : this->gameObjects) {
		gameObject->Update(dt);
	}
	for (const auto &event : this->eventList) {
		this->events[event]->Process(this);
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
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
}

auto createNewGameObject(YAML::Node &object) -> GameObject * {
	GameObject *gameObject;
	if (!object["type"]) {
		object["type"] = "gameObject";
	}
	if (object["type"].as<std::string>() == "staticObject") {
		gameObject = new StaticObject;
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
		this->keyMap[this->adapter.GetKeyCode(
			keyBind["key"].as<std::string>())] =
			keyBind["action"].as<std::string>();
	}

	spdlog::info("State change done.");
}
