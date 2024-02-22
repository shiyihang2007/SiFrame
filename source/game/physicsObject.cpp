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
	if (abs(this->GetVelocityY()) >
		5.0F * config["physics"]["pixelsPerMeter"].as<float>()) {
		this->SetVelocityY(
			5.0F * config["physics"]["pixelsPerMeter"].as<float>() *
			this->GetVelocityY() / abs(this->GetVelocityY()));
	}
	// air friction
	float mu = config["physics"]["airFrictionFactor"].as<float>();
	float vxn =
		this->GetVelocityX() / sqrt(pow(this->GetVelocityX(), 2) +
									pow(this->GetVelocityY(), 2));
	float vyn =
		(this->GetVelocityY() / sqrt(pow(this->GetVelocityX(), 2) +
									 pow(this->GetVelocityY(), 2)));
	float fx =
		abs(this->GetVelocityX()) > 1.0F
			? -static_cast<float>(
				  this->GetMess() *
				  std::min(abs(this->GetVelocityX()),
						   mu * config["physics"]["pixelsPerMeter"]
									.as<float>()) *
				  vxn)
			: 0.0F;
	float fy =
		abs(this->GetVelocityY()) > 1.0F
			? -static_cast<float>(
				  this->GetMess() *
				  std::min(abs(this->GetVelocityY()),
						   mu * config["physics"]["pixelsPerMeter"]
									.as<float>()) *
				  vyn)
			: 0.0F;
	this->AddForce(fx, fy);
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
	auto [v1x, v1y] = obj1->GetVelocity();
	auto [v2x, v2y] = obj2->GetVelocity();
	auto m1 = obj1->GetMess();
	auto m2 = obj2->GetMess();
	// For RigidObject, only do the downside collision
	if (obj1->CheckTag("Rigid") || obj2->CheckTag("Rigid")) {
		if (obj1->CheckTag("Rigid") && obj2->CheckTag("Rigid")) {
			return;
		}
		if (obj1->CheckTag("Rigid")) {
			std::swap(obj1, obj2);
		}
		if (obj1->GetPosY() <
				obj2->GetPosY() + obj2->GetHeight() / 2 ||
			obj2->GetVelocityY() < 0) {
			return;
		}
		obj1->SetVelocityY(v2y * m2 / m1);
		obj2->SetVelocityY(v1y * m1 / m2);
		obj2->SetPosY(obj1->GetPosY() - obj2->GetHeight());
		reinterpret_cast<RigidObject *>(obj2)->ResetJumpAble();
		return;
	}
	// Swap Volocity
	obj1->SetVelocity(v2x * m2 / m1, v2y * m2 / m1);
	obj2->SetVelocity(v1x * m1 / m2, v1y * m1 / m2);
	// Make them sperate
	// if (obj1->GetMess() > obj2->GetMess()) {
	// 	std::swap(obj1, obj2);
	// }
	// if (obj1->GetPosX() + obj1->GetWidth() > obj2->GetPosX() &&
	// 	obj1->GetPosX() < obj2->GetPosX()) {
	// 	obj1->SetPosX(obj2->GetPosX() - obj1->GetWidth());
	// }
	// if (obj1->GetPosX() + obj1->GetWidth() >
	// 		obj2->GetPosX() + obj2->GetWidth() &&
	// 	obj1->GetPosX() < obj2->GetPosX() + obj2->GetWidth()) {
	// 	obj1->SetPosX(obj2->GetPosX() + obj2->GetWidth());
	// }
	// if (obj1->GetPosY() + obj1->GetHeight() > obj2->GetPosY() &&
	// 	obj1->GetPosY() < obj2->GetPosY()) {
	// 	obj1->SetPosY(obj2->GetPosY() - obj1->GetHeight());
	// }
	// if (obj1->GetPosY() + obj1->GetHeight() >
	// 		obj2->GetPosY() + obj2->GetHeight() &&
	// 	obj1->GetPosY() < obj2->GetPosY() + obj2->GetHeight()) {
	// 	obj1->SetPosY(obj2->GetPosY() + obj2->GetHeight());
	// }
}
