#include "game/physicsObject.h"
#include "game/command.h"
#include "game/event.h"

#include "spdlog/spdlog.h"

#include <cmath>

auto PhysicsObject::SetObjectByYaml(const YAML::Node &object)
	-> void {
	this->GameObject::SetObjectByYaml(object);
	GAME_OBJECT_SET_MEMBER_DEFAULT(velocityX, 0.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(velocityY, 0.0F);
	GAME_OBJECT_SET_MEMBER_DEFAULT(mess, 1.0F);
}

auto PhysicsObject::Update(float dt) -> void {
	this->GameObject::Update(dt);
	this->posx += this->velocityX * dt;
	this->posy += this->velocityY * dt;
	if (abs(this->GetVelocityX()) < 1.0F) {
		this->velocityX = 0.0F;
	}
	if (abs(this->GetVelocityY()) < 1.0F) {
		this->velocityY = 0.0F;
	}
	this->AddForce(abs(this->GetVelocityX()) > 1.0F
					   ? -static_cast<float>(
							 (this->GetMess() * 0.5F) *
							 (this->GetVelocityX() /
							  sqrt(pow(this->GetVelocityX(), 2) +
								   pow(this->GetVelocityY(), 2))))
					   : 0.0F,
				   abs(this->GetVelocityY()) > 1.0F
					   ? -static_cast<float>(
							 (this->GetMess() * 0.5F) *
							 (this->GetVelocityY() /
							  sqrt(pow(this->GetVelocityX(), 2) +
								   pow(this->GetVelocityY(), 2))))
					   : 0.0F);
}

void PhysicsObject::InsertObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
	(*events)[this->name + "MoveLeft"] =
		new Event(this, CommandPhysicsMoveLeft::Instance());
	(*events)[this->name + "MoveRight"] =
		new Event(this, CommandPhysicsMoveRight::Instance());
	(*events)[this->name + "MoveUp"] =
		new Event(this, CommandPhysicsMoveUp::Instance());
	(*events)[this->name + "MoveDown"] =
		new Event(this, CommandPhysicsMoveDown::Instance());
}
void PhysicsObject::RemoveObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
	delete (*events)[this->name + "MoveLeft"];
	events->erase(this->name + "MoveLeft");
	delete (*events)[this->name + "MoveRight"];
	events->erase(this->name + "MoveRight");
	delete (*events)[this->name + "MoveUp"];
	events->erase(this->name + "MoveUp");
	delete (*events)[this->name + "MoveDown"];
	events->erase(this->name + "MoveDown");
}

auto PhysicsObject::AddForce(float x, float y) -> void {
	this->velocityX += x / this->mess;
	this->velocityY += y / this->mess;
}

auto CheckCollision(GameObject *obj1, GameObject *obj2)
	-> CollisionType {
	return CollisionType::NONE;
}
auto CheckCollision(PhysicsObject *obj1, GameObject *obj2)
	-> CollisionType {
	return CollisionType::NONE;
}
auto CheckCollision(PhysicsObject *obj1, PhysicsObject *obj2)
	-> CollisionType {
	if (obj1->GetPosX() + obj1->GetWidth() > obj2->GetPosX() &&
		obj1->GetPosX() < obj2->GetPosX() + obj2->GetWidth() &&
		obj1->GetPosY() + obj1->GetHeight() > obj2->GetPosY() &&
		obj1->GetPosY() < obj2->GetPosY() + obj2->GetHeight()) {
		if (obj1->GetVelocityX() - obj2->GetVelocityX() > 0) {
			return CollisionType::LEFT;
		}
		if (obj1->GetVelocityX() - obj2->GetVelocityX() < 0) {
			return CollisionType::RIGHT;
		}
		if (obj1->GetVelocityY() - obj2->GetVelocityY() > 0) {
			return CollisionType::TOP;
		}
		if (obj1->GetVelocityY() - obj2->GetVelocityY() < 0) {
			return CollisionType::BOTTOM;
		}
	}
	return CollisionType::NONE;
}

void OnCollision(PhysicsObject *obj1, PhysicsObject *obj2) {
	spdlog::debug("Collision! {} and {}", obj1->GetName(),
				  obj2->GetName());
	// Swap Volocity
	auto [v1x, v1y] = obj1->GetVelocity();
	auto [v2x, v2y] = obj2->GetVelocity();
	auto m1 = obj1->GetMess();
	auto m2 = obj2->GetMess();
	obj1->SetVelocity(v2x * m2 / m1, v2y * m2 / m1);
	obj2->SetVelocity(v1x * m1 / m2, v1y * m1 / m2);
}
