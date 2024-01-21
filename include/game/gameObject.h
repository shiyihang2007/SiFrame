#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "game/adapter.h"

class GameObject {
  protected:
	std::string spriteId;
	float posx, posy;
	float width, height;
	float rotation;
	float colorR, colorG, colorB;

  public:
	virtual void Update(float dt);
	virtual void Render(Adapter &adapter);
};

#endif
