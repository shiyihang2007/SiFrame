#include "game/gameObject.h"
#include "game/adapter.h"

void GameObject::Update(float dt) {}

void GameObject::Render(Adapter &adapter) {
	adapter.Draw(spriteId.c_str(), this->posx, this->posy,
				 this->width, this->height, this->rotation,
				 this->colorR, this->colorG, this->colorB);
}
