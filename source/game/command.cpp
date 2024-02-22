#include "game/command.h"
#include "game/gameObject.h"
#include "game/physicsObject.h"
#include "game/rigidObject.h"

#include <map>
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
	rigid->AddForce(
		-3.0F * rigid->GetMess() *
			config["physics"]["pixelsPerMeter"].as<float>() *
			deltaTime,
		0.0F);
}
void CommandRigidMoveRight::Execute(GameObject *self, GameBase *game,
									float deltaTime) {
	auto *rigid = reinterpret_cast<RigidObject *>(self);
	rigid->AddForce(
		3.0F * rigid->GetMess() *
			config["physics"]["pixelsPerMeter"].as<float>() *
			deltaTime,
		0.0F);
}
void CommandRigidJump::Execute(GameObject *self, GameBase *game,
							   float deltaTime) {
	auto *rigid = reinterpret_cast<RigidObject *>(self);
	if (rigid->IsVirtual()) {
		return;
	}
	if (rigid->GetJumpAble() == 0) {
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
	// if (rigid->GetJumpAble() != RigidObject::GetJumpAbility()) {
	// 	return;
	// }
	rigid->AddVirtualTime(0.02F);
}
