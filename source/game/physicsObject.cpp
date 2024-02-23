#include "game/physicsObject.h"
#include "game/command.h"
#include "game/event.h"

#include "game/rigidObject.h"
#include "spdlog/spdlog.h"

#include <cmath>
#include <type_traits>

extern YAML::Node config;

auto PhysicsObject::SetObjectByYaml(const YAML::Node &object)
	-> void {
	this->GameObject::SetObjectByYaml(object);
	GAME_OBJECT_SET_MEMBER_DEFAULT(velocityX, 0.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(velocityY, 0.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(mess, 1.0F);
	this->tags.insert("Physics");
}

auto PhysicsObject::Update(float dt) -> void {
	this->GameObject::Update(dt);
	this->posx += this->velocityX * dt *
				  config["physics"]["pixelsPerMeter"].as<float>();
	this->posy += this->velocityY * dt *
				  config["physics"]["pixelsPerMeter"].as<float>();
	if (abs(this->GetVelocityX()) < 0.1F) {
		this->velocityX = 0.0F;
	}
	if (abs(this->GetVelocityY()) < 0.1F) {
		this->velocityY = 0.0F;
	}
	// virtual time
	if (this->virtualTime > 0.0F) {
		this->virtualTime -= dt;
		if (this->virtualTime <= 0.0F) {
			this->virtualTime = 0.0F;
			this->tags.erase("Virtual");
		}
	}
}

void PhysicsObject::InsertObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
}
void PhysicsObject::RemoveObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
}

auto PhysicsObject::AddForce(float x, float y) -> void {
	this->velocityX += x / this->mess;
	this->velocityY += y / this->mess;
}
void PhysicsObject::AddVirtualTime(float time) {
	this->tags.insert("Virtual");
	this->virtualTime += time;
}
auto PhysicsObject::GetVelocity() const -> std::pair<float, float> {
	return {this->velocityX, this->velocityY};
}
auto PhysicsObject::GetVelocityX() const -> float {
	return this->velocityX;
}
auto PhysicsObject::GetVelocityY() const -> float {
	return this->velocityY;
}
void PhysicsObject::SetVelocity(float x, float y) {
	this->velocityX = x;
	this->velocityY = y;
}
void PhysicsObject::SetVelocity(std::pair<float, float> velocity) {
	this->velocityX = velocity.first;
	this->velocityY = velocity.second;
}
void PhysicsObject::SetVelocityX(float x) { this->velocityX = x; }
void PhysicsObject::SetVelocityY(float y) { this->velocityY = y; }
auto PhysicsObject::GetMess() const -> float { return this->mess; }
void PhysicsObject::SetMess(float mess) { this->mess = mess; }

auto PhysicsObject::CheckCollisionWith(
	std::map<std::string, GameObject *> *objects)
	-> std::vector<std::string> {
	std::vector<std::string> collidedObjects;
	for (auto &[key, object] : *objects) {
		if (!object->CheckTag("Physics")) {
			continue;
		}
		if (CheckCollision(
				this, reinterpret_cast<PhysicsObject *>(object))) {
			collidedObjects.push_back(key);
		}
	}
	return collidedObjects;
}

void PhysicsObject::SetColliding(bool isColliding) {
	this->isColliding = isColliding;
}
auto PhysicsObject::IsColliding() const -> bool {
	return this->isColliding;
}

void PhysicsObject::OnCollision(PhysicsObject *obj) {}

auto CheckCollision(PhysicsObject *obj1, PhysicsObject *obj2)
	-> bool {
	if (obj1->CheckTag("Virtual") || obj2->CheckTag("Virtual")) {
		return false;
	}
	if (obj1->GetPosX() + obj1->GetWidth() > obj2->GetPosX() &&
		obj1->GetPosX() <= obj2->GetPosX() + obj2->GetWidth() &&
		obj1->GetPosY() + obj1->GetHeight() > obj2->GetPosY() &&
		obj1->GetPosY() <= obj2->GetPosY() + obj2->GetHeight()) {
		obj1->SetColliding(true);
		obj2->SetColliding(true);
		return true;
	}
	return false;
}

void OnCollision(PhysicsObject *obj1, PhysicsObject *obj2) {
	obj1->OnCollision(obj2);
	obj2->OnCollision(obj1);
}
