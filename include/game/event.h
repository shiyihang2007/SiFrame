#ifndef EVENT_H
#define EVENT_H

#include "game/gameBase.h"
#include "game/gameObject.h"

#include <map>
#include <string>

class Event {
	GameObject *self;
	void (*callback)(GameObject *self, GameBase *game,
					 float deltaTime);

  public:
	Event(GameObject *self,
		  void (*callback)(GameObject *self, GameBase *game,
						   float deltaTime)) {
		this->self = self;
		this->callback = callback;
	}
	void Process(GameBase *game, float deltaTime) {
		this->callback(this->self, game, deltaTime);
	}
};

void InitEvents(std::map<std::string, Event *> *events);

#endif
