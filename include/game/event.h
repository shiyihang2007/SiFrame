#ifndef EVENT_H
#define EVENT_H

#include "game/command.h"
#include "game/gameBase.h"
#include "game/gameObject.h"

#include <map>
#include <string>

class Event {
	GameObject *self;
	Command *command;

  public:
	Event(GameObject *self, Command *command) {
		this->self = self;
		this->command = command;
	}
	~Event() = default;
	void Process(GameBase *game, float deltaTime) {
		this->command->Execute(this->self, game, deltaTime);
	}
};

void InitEvents(std::map<std::string, Event *> *events);

#endif
