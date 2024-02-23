
#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <map>
#include <string>

#include "game/gameState.h"

class GameBase {
  public:
	GameBase() = default;
	virtual ~GameBase() = default;

	virtual void ChangeState(GameState newState) = 0;

	virtual auto GetWidth() -> void * = 0;
	virtual auto GetHeight() -> void * = 0;
	virtual auto GetGameObjects() -> void * = 0;
	virtual auto GetGameState() -> void * = 0;
	virtual auto GetEvents() -> void * = 0;
	virtual auto GetAdapter() -> void * = 0;

	virtual void AddObject(std::string name, void *obj) = 0;
};

#endif
