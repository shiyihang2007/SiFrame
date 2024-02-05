#ifndef EVENT_H
#define EVENT_H

#include "game/gameBase.h"
#include "game/gameObject.h"

#include <map>
#include <string>

class Event {
	GameObject *self;
	void (*callback)(GameObject *self, GameBase *game);

  public:
	Event(GameObject *self,
		  void (*callback)(GameObject *self, GameBase *game)) {
		this->self = self;
		this->callback = callback;
	}
	void Process(GameBase *game) {
		this->callback(this->self, game);
	}
};

void InitEvents(std::map<std::string, Event *> *events);

#endif
