#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <utility>

#include "game/adapter.h"

class GameObject {
  protected:
	std::string spriteId;
	float posx, posy;
	float width, height;
	float rotation;
	float colorR, colorG, colorB;

  public:
	explicit GameObject(std::string spriteId = "unknown",
						float posx = 0.0F, float posy = 0.0F,
						float width = 0.0F, float height = 0.0F,
						float rotation = 0.0F, float colorR = 1.0F,
						float colorG = 1.0F, float colorB = 1.0F)
		: spriteId(std::move(spriteId)), posx(posx), posy(posy),
		  width(width), height(height), rotation(rotation),
		  colorR(colorR), colorG(colorG), colorB(colorB) {}
	virtual ~GameObject() = default;

	void SetSpriteId(std::string spriteId) {
		this->spriteId = std::move(spriteId);
	}
	void SetPosition(float posx, float posy) {
		this->posx = posx;
		this->posy = posy;
	}
	void SetSize(float width, float height) {
		this->width = width;
		this->height = height;
	}
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetColor(float colorR, float colorG, float colorB) {
		this->colorR = colorR;
		this->colorG = colorG;
		this->colorB = colorB;
	}

	virtual void Update(float dt);
	virtual void Render(Adapter &adapter);
};

#endif
