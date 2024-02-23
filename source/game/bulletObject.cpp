#include "game/bulletObject.h"

extern YAML::Node config;

void BulletObject::Update(float dt) {
	PhysicsObject::Update(dt);
	if (lifeTime != -1) {
		lifeTime -= dt;
		if (lifeTime < 0 ||
			(this->posx < 0 ||
			 this->posx > config["window"]["width"].as<float>()) ||
			(this->posy < 0 ||
			 this->posy > config["window"]["height"].as<float>())) {
			this->AddTag("Deleted");
		}
	}
}
void BulletObject::SetObjectByYaml(const YAML::Node &object) {
	PhysicsObject::SetObjectByYaml(object);
	this->AddTag("Bullet");
}
void BulletObject::ResetLifeTime() { lifeTime = 10.0F; }
void BulletObject::SetOwner(GameObject *owner) {
	this->owner = owner;
}
void BulletObject::OnCollision(PhysicsObject *obj) {
	if (obj->CheckTag("Rigid")) {
		if (obj->GetName() == owner->GetName()) {
			return;
		}
		this->AddTag("Deleted");
	}
}
auto BulletObject::GetOwner() const -> GameObject * { return owner; }
