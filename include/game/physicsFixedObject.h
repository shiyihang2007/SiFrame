#ifndef PHYSICS_FIXED_OBJECT_H
#define PHYSICS_FIXED_OBJECT_H

#include "game/physicsObject.h"

class PhysicsFixedObject : public PhysicsObject {
  public:
	PhysicsFixedObject() = default;
	~PhysicsFixedObject() override = default;

	void SetObjectByYaml(const YAML::Node &object) override {
		PhysicsObject::SetObjectByYaml(object);
		tags.insert("Fixed");
	}

	void AddForce(float x, float y) override {}

	void SetVelocity(float x, float y) override {}
	void SetVelocity(std::pair<float, float> velocity) override {}
	void SetVelocityX(float x) override {}
	void SetVelocityY(float y) override {}
};

#endif
