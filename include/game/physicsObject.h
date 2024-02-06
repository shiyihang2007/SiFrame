#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "game/gameObject.h"

#include <utility>

class PhysicsObject : public GameObject {
  protected:
	float velocityX, velocityY;
	float mess;

  public:
	PhysicsObject() = default;

	void SetObjectByYaml(const YAML::Node &object) override;

	void Update(float dt) override;

	void InsertObjectEvents(void *events) override;
	void RemoveObjectEvents(void *events) override;

	virtual void AddForce(float x, float y);

	[[nodiscard]] virtual auto GetVelocity() const
		-> std::pair<float, float> {
		return {this->velocityX, this->velocityY};
	}
	[[nodiscard]] virtual auto GetVelocityX() const -> float {
		return this->velocityX;
	}
	[[nodiscard]] virtual auto GetVelocityY() const -> float {
		return this->velocityY;
	}
	virtual void SetVelocity(float x, float y) {
		this->velocityX = x;
		this->velocityY = y;
	}
	virtual void SetVelocity(std::pair<float, float> velocity) {
		this->velocityX = velocity.first;
		this->velocityY = velocity.second;
	}
	virtual void SetVelocityX(float x) { this->velocityX = x; }
	virtual void SetVelocityY(float y) { this->velocityY = y; }
	[[nodiscard]] virtual auto GetMess() const -> float {
		return this->mess;
	}
	virtual void SetMess(float mess) { this->mess = mess; }
};

enum class CollisionType { NONE, LEFT, RIGHT, TOP, BOTTOM };

auto CheckCollision(GameObject *obj1, GameObject *obj2)
	-> CollisionType;
auto CheckCollision(PhysicsObject *obj1, GameObject *obj2)
	-> CollisionType;
auto CheckCollision(PhysicsObject *obj1, PhysicsObject *obj2)
	-> CollisionType;

void OnCollision(PhysicsObject *obj1, PhysicsObject *obj2);

#endif
