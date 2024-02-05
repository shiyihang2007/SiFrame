#include "game/gameObject.h"
#include "game/adapter.h"
#include "game/event.h"

void GameObject::Update(float dt) {}

void GameObject::Render(Adapter *adapter) {
	adapter->Draw(spriteId.c_str(), this->posx, this->posy,
				  this->width, this->height, this->rotation,
				  this->colorR, this->colorG, this->colorB);
}

void GameObject::SetObjectByYaml(const YAML::Node &object) {
	this->name = object.Tag();
	GAME_OBJECT_SET_MEMBER_DEFAULT(spriteId, "unknown");
	GAME_OBJECT_SET_MEMBER_DEFAULT(posx, 0.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(posy, 0.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(width, 10.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(height, 10.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(rotation, 0.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(colorR, 1.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(colorG, 1.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(colorB, 1.0F);
}

void GameObject::InsertObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
	(*events)[this->name + "MoveLeft"] =
		new Event(this, [](GameObject *self, GameBase *game) {
			self->posx -= 10.0F;
		});
	(*events)[this->name + "MoveRight"] =
		new Event(this, [](GameObject *self, GameBase *game) {
			self->posx += 10.0F;
		});
	(*events)[this->name + "MoveTop"] =
		new Event(this, [](GameObject *self, GameBase *game) {
			self->posy -= 10.0F;
		});
	(*events)[this->name + "MoveButtom"] =
		new Event(this, [](GameObject *self, GameBase *game) {
			self->posy += 10.0F;
		});
}

void GameObject::RemoveObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
	events->erase(this->name + "MoveLeft");
	events->erase(this->name + "MoveRight");
	events->erase(this->name + "MoveTop");
	events->erase(this->name + "MoveButtom");
}
