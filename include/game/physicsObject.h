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

	[[nodiscard]] auto IsVirtual() const -> bool {
		return virtualTime > 0.0F;
	}

	void InsertObjectEvents(void *events) override;
	void RemoveObjectEvents(void *events) override;

	virtual void AddForce(float x, float y);
	void AddVirtualTime(float time) {
		this->tags.insert("Virtual");
		this->virtualTime += time;
	}

	[[nodiscard]] auto GetVelocity() const
		-> std::pair<float, float> {
		return {this->velocityX, this->velocityY};
	}
	[[nodiscard]] auto GetVelocityX() const -> float {
		return this->velocityX;
	}
	[[nodiscard]] auto GetVelocityY() const -> float {
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
	[[nodiscard]] auto GetMess() const -> float {
		return this->mess;
	}
	void SetMess(float mess) { this->mess = mess; }

	void SetColliding(bool isColliding) {
		this->isColliding = isColliding;
	}
	[[nodiscard]] auto IsColliding() const -> bool {
		return this->isColliding;
	}

	auto
	CheckCollisionWith(std::map<std::string, GameObject *> *objects)
		-> std::vector<std::string>;
};

auto CheckCollision(PhysicsObject *obj1, PhysicsObject *obj2)
	-> bool;

void OnCollision(PhysicsObject *obj1, PhysicsObject *obj2);

#endif
