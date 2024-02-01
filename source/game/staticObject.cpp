#include "game/staticObject.h"

void StaticObject::SetObjectByYaml(const YAML::Node &object) {
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