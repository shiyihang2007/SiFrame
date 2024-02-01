#include "game/gameObject.h"
#include "game/adapter.h"

void GameObject::Update(float dt) {}

void GameObject::Render(Adapter *adapter) {
	adapter->Draw(spriteId.c_str(), this->posx, this->posy,
				  this->width, this->height, this->rotation,
				  this->colorR, this->colorG, this->colorB);
}

void GameObject::SetObjectByYaml(const YAML::Node &object) {
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
