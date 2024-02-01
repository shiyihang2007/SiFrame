#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <utility>

#include "game/adapter.h"

#include "yaml-cpp/yaml.h"

#define GAME_OBJECT_SET_MEMBER(member, nodeName, defaultValue)      \
	member = object[#member]                                        \
				 ? object[nodeName].as<decltype(member)>()          \
				 : defaultValue
#define GAME_OBJECT_SET_MEMBER_DEFAULT(member, defaultValue)        \
	member = object[#member]                                        \
				 ? object[#member].as<decltype(member)>()           \
				 : defaultValue
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

	virtual void SetObjectByYaml(const YAML::Node &object);

	virtual void Update(float dt);
	virtual void Render(Adapter *adapter);
};

#endif
