#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
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
	std::string name;
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
	virtual void InsertObjectEvents(void *events);
	virtual void RemoveObjectEvents(void *events);

	virtual void Update(float dt);
	virtual void Render(Adapter *adapter);

	[[nodiscard]] virtual auto GetOnClickEvent() const
		-> std::string {
		return "none";
	}

	[[nodiscard]] auto GetName() const -> std::string {
		return this->name;
	}

	void SetPosX(float posx) { this->posx = posx; }
	[[nodiscard]] auto GetPosX() const -> float {
		return this->posx;
	}
	void SetPosY(float posy) { this->posy = posy; }
	[[nodiscard]] auto GetPosY() const -> float {
		return this->posy;
	}
	void SetWidth(float width) { this->width = width; }
	[[nodiscard]] auto GetWidth() const -> float {
		return this->width;
	}
	void SetHeight(float height) { this->height = height; }
	[[nodiscard]] auto GetHeight() const -> float {
		return this->height;
	}
	void SetRotation(float rotation) { this->rotation = rotation; }
	[[nodiscard]] auto GetRotation() const -> float {
		return this->rotation;
	}
};

#endif
