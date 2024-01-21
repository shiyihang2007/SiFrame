#include "game/game.h"
#include "game/adapter.h"
#include "resource_manager.h"

void GameProject::Init() {
	this->adapter.Init(this->width, this->height);
}

void GameProject::ProcessInput(float dt) {}

void GameProject::Update(float dt) {
	for (auto [key, gameObject] : this->gameObjects) {
		gameObject->Update(dt);
	}
}

void GameProject::Render() {
	for (auto [key, gameObject] : this->gameObjects) {
		gameObject->Render(this->adapter);
	}
}

void GameProject::CleanUp() {
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
}
