#include "game/game.h"
#include "game/adapter.h"
#include "game/gameObject.h"
#include "resource_manager.h"

#include "spdlog/spdlog.h"
#include "yaml-cpp/yaml.h"

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

	spdlog::info("Loading Objects...");
	this->changeState("MainMenu");
	spdlog::info("Game Inited.");
}

void GameProject::ProcessInput(float dt) {}

void GameProject::Update(float dt) {
	for (auto [key, gameObject] : this->gameObjects) {
		gameObject->Update(dt);
	}
}

void GameProject::Render() {
	for (auto [key, gameObject] : this->gameObjects) {
		gameObject->Render(&this->adapter);
	}
}

void GameProject::CleanUp() {
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
}

auto createNewGameObject(YAML::Node object) -> GameObject * {
	GameObject *gameObject;
	if (!object["type"] ||
		object["type"].as<std::string>() == "gameObject") {
		gameObject = new GameObject;
	}

	spdlog::debug(
		"createObject: (spriteId:{}, position:({},{}), "
		"size:({},{}), rotation:{}, color:({},{},{}))",
		object["spriteId"] ? object["spriteId"].as<std::string>()
						   : "unknown",
		object["posx"] ? object["posx"].as<float>() : 0.0F,
		object["posy"] ? object["posy"].as<float>() : 0.0F,
		object["width"] ? object["width"].as<float>() : 10.0F,
		object["height"] ? object["height"].as<float>() : 10.0F,
		object["rotation"] ? object["rotation"].as<float>() : 0.0F,
		object["colorR"] ? object["colorR"].as<float>() : 1.0F,
		object["colorG"] ? object["colorG"].as<float>() : 1.0F,
		object["colorB"] ? object["colorB"].as<float>() : 1.0F);

	gameObject->SetObjectByYaml(object);
	return gameObject;
}
void GameProject::changeState(GameState newState) {
	this->gameState = std::move(newState);
	for (auto [key, gameObject] : this->gameObjects) {
		delete gameObject;
	}
	this->gameObjects.clear();

	YAML::Node stateInfo = config["states"][this->gameState];
	for (auto &&object : stateInfo) {
		this->gameObjects[object["name"].as<std::string>()] =
			createNewGameObject(object);
		spdlog::debug("Loaded object '{}'",
					  object["name"].as<std::string>());
	}
}
