#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "game/gameObject.h"

class StaticObject : public GameObject {
  public:
	explicit StaticObject(std::string spriteId = "unknown",
						  float posx = 0.0F, float posy = 0.0F,
						  float width = 0.0F, float height = 0.0F,
						  float rotation = 0.0F, float colorR = 1.0F,
						  float colorG = 1.0F, float colorB = 1.0F)
		: GameObject(std::move(spriteId), posx, posy, width, height,
					 rotation, colorR, colorG, colorB) {}

	~StaticObject() override = default;

	void SetObjectByYaml(const YAML::Node &object) override;
};

#endif
