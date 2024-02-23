#ifndef RIGID_OBJECT_H
#define RIGID_OBJECT_H

#include "game/gameObject.h"
#include "game/physicsObject.h"

class RigidObject : public PhysicsObject {
  public:
	enum Face { LEFT, RIGHT };

  private:
	Face facing;

  protected:
	float jumpColdDown = 0;
	int jumpAble = 0;

	float fireColdDown = 0;
	float fireColdDownTime;

  public:
	RigidObject() = default;
	~RigidObject() override = default;

	void SetObjectByYaml(const YAML::Node &object) override;

	void Update(float dt) override;

	void OnCollision(PhysicsObject *obj) override;

	void InsertObjectEvents(void *events) override;
	void RemoveObjectEvents(void *events) override;

	void SetFacing(Face facing) { this->facing = facing; }
	[[nodiscard]] auto GetFacing() const -> Face { return facing; }

	auto ResetJumpAble() -> void;
	auto SubJumpAble() -> void;

	auto GetJumpColdDown() -> float &;
	auto ResetJumpColdDown() -> void;

	auto GetFireColdDown() -> float &;
	auto ResetFireColdDown() -> void;
};

#endif
