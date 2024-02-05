#include "game/event.h"

void InitEvents(std::map<std::string, Event *> *events) {
	(*events)["none"] =
		new Event(nullptr, [](GameObject *self, GameBase *game,
							  float deltaTime) { ; });
	(*events)["switchStateToMainMenu"] =
		new Event(nullptr, [](GameObject *self, GameBase *game,
							  float deltaTime) {
			game->ChangeState("MainMenu");
		});
	(*events)["switchStateToGamePlay"] =
		new Event(nullptr, [](GameObject *self, GameBase *game,
							  float deltaTime) {
			game->ChangeState("GamePlay");
		});
}
