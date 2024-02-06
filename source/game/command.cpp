#include "game/command.h"
#include "game/physicsObject.h"

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

void CommandMoveLeft::Execute(GameObject *self, GameBase *game,
							  float deltaTime) {
	self->SetPosY(self->GetPosY() - 30.0F * deltaTime);
}
void CommandMoveRight::Execute(GameObject *self, GameBase *game,
							   float deltaTime) {
	self->SetPosY(self->GetPosY() + 30.0F * deltaTime);
}
void CommandMoveUp::Execute(GameObject *self, GameBase *game,
							float deltaTime) {
	self->SetPosX(self->GetPosX() - 30.0F * deltaTime);
}
void CommandMoveDown::Execute(GameObject *self, GameBase *game,
							  float deltaTime) {
	self->SetPosX(self->GetPosX() + 30.0F * deltaTime);
}

void CommandPhysicsMoveLeft::Execute(GameObject *self,
									 GameBase *game,
									 float deltaTime) {
	reinterpret_cast<PhysicsObject *>(self)->AddForce(
		-300.0F * deltaTime, 0.0F);
}
void CommandPhysicsMoveRight::Execute(GameObject *self,
									  GameBase *game,
									  float deltaTime) {
	reinterpret_cast<PhysicsObject *>(self)->AddForce(
		300.0F * deltaTime, 0.0F);
}
void CommandPhysicsMoveUp::Execute(GameObject *self, GameBase *game,
								   float deltaTime) {
	reinterpret_cast<PhysicsObject *>(self)->AddForce(
		0.0F, -300.0F * deltaTime);
}
void CommandPhysicsMoveDown::Execute(GameObject *self,
									 GameBase *game,
									 float deltaTime) {
	reinterpret_cast<PhysicsObject *>(self)->AddForce(
		0.0F, 300.0F * deltaTime);
}
