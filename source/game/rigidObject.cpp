#include "game/rigidObject.h"
#include "game/command.h"
#include "game/event.h"

#include "spdlog/spdlog.h"

extern YAML::Node config;

void RigidObject::SetObjectByYaml(const YAML::Node &object) {
	PhysicsObject::SetObjectByYaml(object);
	this->tags.insert("Rigid");
}

void RigidObject::Update(float dt) {
	this->PhysicsObject::Update(dt);
	this->jumpColdDown = std::max(0.0F, this->jumpColdDown - dt);
	// on-plate friction
	if (this->GetJumpAble() == RigidObject::GetJumpAbility() &&
		abs(this->GetVelocityX()) > 0.1F) {
		this->AddForce(
			(this->GetVelocityX() < 0 ? 1.0F : -1.0F) *
				std::min(abs(this->GetVelocityX()),
						 config["physics"]["plateFrictionFactor"]
								 .as<float>() *
							 config["physics"]["pixelsPerMeter"]
								 .as<float>() *
							 dt) *
				this->GetMess(),
			0.0F);
	}
	// gravity
	this->AddForce(
		0.0F, config["physics"]["gravity"].as<float>() *
				  this->GetMess() * dt *
				  config["physics"]["pixelsPerMeter"].as<float>());
	// limit fall speed
	if (this->velocityY >
		2.0F * config["physics"]["pixelsPerMeter"].as<float>()) {
		this->velocityY =
			2.0F * config["physics"]["pixelsPerMeter"].as<float>();
	}
}

void RigidObject::InsertObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
	(*events)[this->name + "MoveLeft"] =
		new Event(this, CommandRigidMoveLeft::Instance());
	(*events)[this->name + "MoveRight"] =
		new Event(this, CommandRigidMoveRight::Instance());
	(*events)[this->name + "MoveUp"] =
		(*events)[this->name + "Jump"] =
			new Event(this, CommandRigidJump::Instance());
	(*events)[this->name + "MoveDown"] =
		(*events)[this->name + "Fall"] =
			new Event(this, CommandRigidFall::Instance());
}
void RigidObject::RemoveObjectEvents(void *eventsV) {
	auto *events =
		reinterpret_cast<std::map<std::string, Event *> *>(eventsV);
	delete (*events)[this->name + "MoveLeft"];
	events->erase(this->name + "MoveLeft");
	delete (*events)[this->name + "MoveRight"];
	events->erase(this->name + "MoveRight");
	delete (*events)[this->name + "Jump"];
	events->erase(this->name + "Jump");
	events->erase(this->name + "MoveUp");
	delete (*events)[this->name + "Fall"];
	events->erase(this->name + "Fall");
	events->erase(this->name + "MoveDown");
}

auto RigidObject::GetJumpAbility() -> int {
	return config["physics"]["jumpAbility"].as<int>();
}
auto RigidObject::GetJumpColdDownTime() -> float {
	return config["physics"]["jumpColdDownTime"].as<float>();
}
