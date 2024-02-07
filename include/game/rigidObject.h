#ifndef RIGID_OBJECT_H
#define RIGID_OBJECT_H

#include "game/physicsObject.h"

class RigidObject : public PhysicsObject {
  protected:
	int jumpAble = 0;
	float jumpColdDown = 0;

  public:
	RigidObject() = default;
	~RigidObject() override = default;

	[[nodiscard]] auto IsRigid() const -> bool override {
		return true;
	}

	void Update(float dt) override;

	void InsertObjectEvents(void *events) override;
	void RemoveObjectEvents(void *events) override;

	auto GetJumpAble() -> int & { return jumpAble; }
	static auto GetJumpAbility() -> int;
	auto ResetJumpAble() -> void { jumpAble = GetJumpAbility(); }
	auto SubJumpAble() -> void { jumpAble > 0 ? --jumpAble : 0; }

	auto GetJumpColdDown() -> float & { return jumpColdDown; }
	static auto GetJumpColdDownTime() -> float;
	auto ResetJumpColdDown() -> void {
		jumpColdDown = GetJumpColdDownTime();
	}
};

#endif
