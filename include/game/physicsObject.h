#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "game/gameObject.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

class PhysicsObject : public GameObject {
  protected:
	float velocityX, velocityY;
	float mess;

	bool isColliding = false;

	float virtualTime = 0.0F;

  public:
	PhysicsObject() = default;

	void SetObjectByYaml(const YAML::Node &object) override;

	void Update(float dt) override;

	void InsertObjectEvents(void *events) override;
	void RemoveObjectEvents(void *events) override;

	virtual void AddForce(float x, float y);

	void AddVirtualTime(float time);

	[[nodiscard]] auto GetVelocity() const
		-> std::pair<float, float>;
	[[nodiscard]] auto GetVelocityX() const -> float;
	[[nodiscard]] auto GetVelocityY() const -> float;

	virtual void SetVelocity(float x, float y);
	virtual void SetVelocity(std::pair<float, float> velocity);
	virtual void SetVelocityX(float x);
	virtual void SetVelocityY(float y);

	[[nodiscard]] auto GetMess() const -> float;
	void SetMess(float mess);

	void SetColliding(bool isColliding);
	[[nodiscard]] auto IsColliding() const -> bool;

	virtual void OnCollision(PhysicsObject *obj);

	auto
	CheckCollisionWith(std::map<std::string, GameObject *> *objects)
		-> std::vector<std::string>;
};

auto CheckCollision(PhysicsObject *obj1, PhysicsObject *obj2)
	-> bool;

void OnCollision(PhysicsObject *obj1, PhysicsObject *obj2);

#endif
