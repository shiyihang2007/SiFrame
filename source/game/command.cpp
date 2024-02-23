#include "game/command.h"
#include "game/bulletObject.h"
#include "game/gameObject.h"
#include "game/physicsObject.h"
#include "game/rigidObject.h"

#include <chrono>
#include <map>
#include <numbers>
#include <string>

extern YAML::Node config;

void CommandNone::Execute(GameObject *self, GameBase *game,
						  float deltaTime) {}

void CommandSwitchStateToMainMenu::Execute(GameObject *self,
										   GameBase *game,
										   float deltaTime) {
	game->ChangeState("MainMenu");
}
void CommandSwitchStateToGamePlay::Execute(GameObject *self,
										   GameBase *game,
										   float deltaTime) {
	game->ChangeState("GamePlay");
}

void CommandRigidMoveLeft::Execute(GameObject *self, GameBase *game,
								   float deltaTime) {
	auto *rigid = reinterpret_cast<RigidObject *>(self);
	rigid->SetFacing(RigidObject::LEFT);
	rigid->AddForce(
		-3.0F * rigid->GetMess() *
			config["physics"]["pixelsPerMeter"].as<float>() *
			deltaTime,
		0.0F);
}
void CommandRigidMoveRight::Execute(GameObject *self, GameBase *game,
									float deltaTime) {
	auto *rigid = reinterpret_cast<RigidObject *>(self);
	rigid->SetFacing(RigidObject::RIGHT);
	rigid->AddForce(
		3.0F * rigid->GetMess() *
			config["physics"]["pixelsPerMeter"].as<float>() *
			deltaTime,
		0.0F);
}
void CommandRigidJump::Execute(GameObject *self, GameBase *game,
							   float deltaTime) {
	auto *rigid = reinterpret_cast<RigidObject *>(self);
	if (rigid->CheckTag("Virtual")) {
		return;
	}
	if (!rigid->CheckTag("JumpAble")) {
		return;
	}
	if (rigid->GetJumpColdDown() != 0) {
		return;
	}
	rigid->SubJumpAble();
	rigid->ResetJumpColdDown();
	rigid->SetVelocityY(0.0F);
	rigid->AddForce(
		0.0F, -1.0F * rigid->GetMess() *
				  config["physics"]["pixelsPerMeter"].as<float>());
	rigid->AddVirtualTime(0.1F);
}
void CommandRigidFall::Execute(GameObject *self, GameBase *game,
							   float deltaTime) {
	auto *rigid = reinterpret_cast<RigidObject *>(self);
	rigid->AddTag("Fall");
	rigid->AddForce(
		0.0F, 0.1F * rigid->GetMess() *
				  config["physics"]["pixelsPerMeter"].as<float>());
}
void CommandRigidFire::Execute(GameObject *self, GameBase *game,
							   float deltaTime) {
	auto *rigid = reinterpret_cast<RigidObject *>(self);
	if (rigid->GetFireColdDown() > 0) {
		return;
	}
	auto *bullet =
		new BulletObject(*(reinterpret_cast<BulletObject *>(
			reinterpret_cast<std::map<std::string, GameObject *> *>(
				game->GetGameObjects())
				->find("BulletPrototype")
				->second)));
	bullet->AddForce(
		rigid->GetFacing() == RigidObject::LEFT
			? -1 * config["physics"]["pixelsPerMeter"].as<float>()
			: 1 * config["physics"]["pixelsPerMeter"].as<float>(),
		0.0F);
	bullet->SetPosX(
		self->GetPosX() + self->GetWidth() / 2 -
		bullet->GetWidth() / 2 /* +
		(rigid->GetFacing() == RigidObject::LEFT ? -1.0F : 1.0F) *
			self->GetWidth() */);
	bullet->SetPosY(self->GetPosY() + self->GetHeight() / 2 -
					bullet->GetHeight() / 2);
	bullet->SetRotation(
		rigid->GetFacing() == RigidObject::LEFT ? 180.0F : 0.0F);
	bullet->SetOwner(self);
	bullet->ResetLifeTime();
	game->AddObject(
		self->GetName() + "_Bullet#" +
			std::to_string(std::chrono::system_clock::now()
							   .time_since_epoch()
							   .count()),
		bullet);
	rigid->AddForce(
		(rigid->GetFacing() == RigidObject::LEFT
			 ? 0.2F * config["physics"]["pixelsPerMeter"].as<float>()
			 : -0.2F *
				   config["physics"]["pixelsPerMeter"].as<float>()) /
			rigid->GetMess(),
		-0.1F * config["physics"]["pixelsPerMeter"].as<float>());
	rigid->ResetFireColdDown();
}
