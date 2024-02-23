
#ifndef GAME_H
#define GAME_H

#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "game/adapter.h"
#include "game/event.h"
#include "game/gameBase.h"
#include "game/gameObject.h"
#include "game/gameState.h"
#include "game/physicsObject.h"
#include "game/staticObject.h"

class GameProject : public GameBase {
	int width, height;

	Adapter adapter;
	std::map<std::string, GameObject *> gameObjects;
	std::multimap<double, std::string, std::greater<>> zIndexQueue;
	std::map<std::string, Event *> events;

	GameState gameState;

	std::map<int, std::string> keyMap;

	std::vector<std::string> eventList;

  public:
	GameProject(int width, int height);
	~GameProject() override;

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	void CleanUp();

	void ChangeState(GameState newState) override;

	auto GetWidth() -> void * override;
	auto GetHeight() -> void * override;
	auto GetGameObjects() -> void * override;
	auto GetGameState() -> void * override;
	auto GetEvents() -> void * override;
	auto GetAdapter() -> void * override;

	void AddObject(std::string name, void *obj) override;
};

#endif
