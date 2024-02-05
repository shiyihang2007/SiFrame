
#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <vector>

#include "game/adapter.h"
#include "game/event.h"
#include "game/gameBase.h"
#include "game/gameObject.h"
#include "game/gameState.h"

class GameProject : public GameBase {
	int width, height;

	Adapter adapter;
	std::map<std::string, GameObject *> gameObjects;
	std::map<std::string, Event *> events;

	GameState gameState;

	std::map<int, std::string> keyMap;

	std::vector<std::string> eventList;

  public:
	GameProject(int width, int height)
		: width(width), height(height) {}

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	void CleanUp();

	void ChangeState(GameState newState) override;

	auto GetWidth() -> void * override { return &width; }
	auto GetHeight() -> void * override { return &height; }
	auto GetGameObjects() -> void * override { return &gameObjects; }
	auto GetGameState() -> void * override { return &gameState; }
	auto GetEvents() -> void * override { return &events; }
	auto GetAdapter() -> void * override { return &adapter; }
};

#endif
