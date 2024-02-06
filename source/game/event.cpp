#include "game/event.h"
#include "game/command.h"

void InitEvents(std::map<std::string, Event *> *events) {
	(*events)["none"] = new Event(nullptr, CommandNone::Instance());
	(*events)["switchStateToMainMenu"] =
		new Event(nullptr, CommandSwitchStateToMainMenu::Instance());
	(*events)["switchStateToGamePlay"] =
		new Event(nullptr, CommandSwitchStateToGamePlay::Instance());
}
