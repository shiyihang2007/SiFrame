#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "game/gameObject.h"

#include <string>

class StaticObject : public GameObject {
	std::string onClickEvent;

  public:
	explicit StaticObject(std::string spriteId = "unknown",
						  float posx = 0.0F, float posy = 0.0F,
						  float width = 0.0F, float height = 0.0F,
						  float rotation = 0.0F, float colorR = 1.0F,
						  float colorG = 1.0F, float colorB = 1.0F,
						  std::string onClickEvent = "none")
		: GameObject(std::move(spriteId), posx, posy, width, height,
					 rotation, colorR, colorG, colorB),
		  onClickEvent(std::move(onClickEvent)) {}
	~StaticObject() override = default;

	void SetObjectByYaml(const YAML::Node &object) override;

	[[nodiscard]] auto GetOnClickEvent() const
		-> std::string override {
		return this->onClickEvent;
	}
};

#endif
