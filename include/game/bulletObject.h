#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H

#include "game/gameObject.h"
#include "game/physicsObject.h"

// TODO(shiyihang): this class should be refactor soon
class BulletObject : public PhysicsObject {
	float lifeTime = -1;
	GameObject *owner;

  public:
	void SetOwner(GameObject *owner);
	[[nodiscard]] auto GetOwner() const -> GameObject *;
	void Update(float dt) override;
	void OnCollision(PhysicsObject *obj) override;
	void SetObjectByYaml(const YAML::Node &object) override;
	void ResetLifeTime();
};

#endif
