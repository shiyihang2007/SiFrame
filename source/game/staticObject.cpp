#include "game/staticObject.h"

void StaticObject::SetObjectByYaml(const YAML::Node &object) {
	this->GameObject::SetObjectByYaml(object);
	GAME_OBJECT_SET_MEMBER_DEFAULT(onClickEvent, "none");
}
