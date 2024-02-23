#ifndef RELATED_OBJECT_H
#define RELATED_OBJECT_H

#include "game/gameObject.h"

class RelatedObject : public GameObject {
	GameObject *father;

  public:
	auto SetObjectByYaml(const YAML::Node &object) -> void override {
		GameObject::SetObjectByYaml(object);
		this->AddTag("Related");
	}

	void SetFather(GameObject *father) { this->father = father; }
	[[nodiscard]] auto GetFather() const -> GameObject * {
		return this->father;
	}

	void Update(float dt) override {
		GameObject::Update(dt);
		this->posx = father->GetPosX();
		this->posy = father->GetPosY();
	}
};

#endif
