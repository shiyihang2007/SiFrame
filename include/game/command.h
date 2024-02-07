#ifndef COMMAND_H
#define COMMAND_H

#include "game/gameBase.h"
#include "game/gameObject.h"

class Command {
  protected:
	Command() = default;

  public:
	virtual ~Command() = default;

	virtual void Execute(GameObject *self, GameBase *game,
						 float deltaTime) = 0;
};

class CommandNone : public Command {
  protected:
	CommandNone() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandNone _instance;
		return &_instance;
	}
};

class CommandSwitchStateToMainMenu : public Command {
  protected:
	CommandSwitchStateToMainMenu() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandSwitchStateToMainMenu _instance;
		return &_instance;
	}
};
class CommandSwitchStateToGamePlay : public Command {
  protected:
	CommandSwitchStateToGamePlay() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandSwitchStateToGamePlay _instance;
		return &_instance;
	}
};

class CommandRigidMoveLeft : public Command {
  protected:
	CommandRigidMoveLeft() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandRigidMoveLeft _instance;
		return &_instance;
	}
};
class CommandRigidMoveRight : public Command {
  protected:
	CommandRigidMoveRight() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandRigidMoveRight _instance;
		return &_instance;
	}
};
class CommandRigidJump : public Command {
  protected:
	CommandRigidJump() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandRigidJump _instance;
		return &_instance;
	}
};
class CommandRigidFall : public Command {
  protected:
	CommandRigidFall() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandRigidFall _instance;
		return &_instance;
	}
};

#endif
