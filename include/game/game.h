
#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

#include "game/adapter.h"
#include "game/gameObject.h"

class GameProject {
	int width, height;

	Adapter adapter;
	std::map<std::string, GameObject *> gameObjects;

  public:
	GameProject(int width, int height)
		: width(width), height(height) {}

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	void CleanUp();

	auto GetAdapter() -> Adapter & { return adapter; }
	[[nodiscard]] auto GetAdapter() const -> const Adapter & {
		return adapter;
	}
};

#endif
