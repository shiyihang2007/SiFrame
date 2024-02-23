#include "game/rigidObject.h"
#include "game/bulletObject.h"
#include "game/command.h"
#include "game/event.h"

#include "game/gameObject.h"
#include "game/physicsObject.h"
#include "spdlog/spdlog.h"

#include <random>

extern YAML::Node config;
extern std::mt19937 rnd;

void RigidObject::SetObjectByYaml(const YAML::Node &object) {
	PhysicsObject::SetObjectByYaml(object);
	facing = LEFT;
	this->tags.insert("Rigid");
	GAME_OBJECT_SET_MEMBER_DEFAULT(fireColdDownTime, 0.3);
}

void RigidObject::Update(float dt) {
	this->PhysicsObject::Update(dt);
	this->jumpColdDown = std::max(0.0F, this->jumpColdDown - dt);
	this->fireColdDown = std::max(0.0F, this->fireColdDown - dt);
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
	// on-plate friction
	if (this->IsColliding() && abs(this->GetVelocityX()) > 0.1F) {
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
	// reborn
	if (this->posy > 2.0F * config["window"]["height"].as<float>()) {
		this->posy = -100.0F;
		this->posx =
			std::uniform_real_distribution<float>(0.2, 0.8)(rnd) *
			config["window"]["width"].as<float>();
		this->velocityX = 0.0F;
		this->velocityY = 0.0F;
	}
	// fall
	if (!this->IsColliding()) {
		this->RemoveTag("Fall");
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
	(*events)[this->name + "Fire"] =
		new Event(this, CommandRigidFire::Instance());
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
	delete (*events)[this->name + "Fire"];
	events->erase(this->name + "Fire");
}

void RigidObject::OnCollision(PhysicsObject *obj) {
	if (obj->CheckTag("Fixed")) {
		if (this->CheckTag("Fall") || this->velocityY <= 0.0F ||
			this->posy + this->height / 2 >= obj->GetPosY()) {
			return;
		}
		this->velocityY = 0.0F;
		this->SetPosY(obj->GetPosY() - this->GetHeight());
		this->ResetJumpAble();
		return;
	}
	if (obj->CheckTag("Bullet")) {
		if (reinterpret_cast<BulletObject *>(obj)
				->GetOwner()
				->GetName() == this->GetName()) {
			return;
		}
		this->AddForce(
			obj->GetVelocityX() * obj->GetMess(),
			-0.1F * config["physics"]["pixelsPerMeter"].as<float>());
	}
}

auto RigidObject::SubJumpAble() -> void {
	if (jumpAble > 0) {
		--jumpAble;
		if (jumpAble == 0) {
			this->RemoveTag("JumpAble");
		}
	}
}
auto RigidObject::ResetJumpAble() -> void {
	this->AddTag("JumpAble");
	jumpAble = config["physics"]["jumpAbility"].as<int>();
}
auto RigidObject::GetJumpColdDown() -> float & {
	return jumpColdDown;
}
auto RigidObject::ResetJumpColdDown() -> void {
	jumpColdDown = config["physics"]["jumpColdDownTime"].as<float>();
}
auto RigidObject::GetFireColdDown() -> float & {
	return fireColdDown;
}
auto RigidObject::ResetFireColdDown() -> void {
	fireColdDown = this->fireColdDownTime;
}
