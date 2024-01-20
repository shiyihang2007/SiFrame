#include "game/adapter.h"

#ifndef GAME_H
#define GAME_H

class GameProject {
	int width, height;

	Adapter adapter;

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
