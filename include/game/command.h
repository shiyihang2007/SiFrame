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

class CommandMoveUp : public Command {
  protected:
	CommandMoveUp() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandMoveUp _instance;
		return &_instance;
	}
};
class CommandMoveDown : public Command {
  protected:
	CommandMoveDown() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandMoveDown _instance;
		return &_instance;
	}
};
class CommandMoveLeft : public Command {
  protected:
	CommandMoveLeft() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandMoveLeft _instance;
		return &_instance;
	}
};
class CommandMoveRight : public Command {
  protected:
	CommandMoveRight() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandMoveRight _instance;
		return &_instance;
	}
};

class CommandPhysicsMoveUp : public Command {
  protected:
	CommandPhysicsMoveUp() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandPhysicsMoveUp _instance;
		return &_instance;
	}
};
class CommandPhysicsMoveDown : public Command {
  protected:
	CommandPhysicsMoveDown() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandPhysicsMoveDown _instance;
		return &_instance;
	}
};
class CommandPhysicsMoveLeft : public Command {
  protected:
	CommandPhysicsMoveLeft() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandPhysicsMoveLeft _instance;
		return &_instance;
	}
};
class CommandPhysicsMoveRight : public Command {
  protected:
	CommandPhysicsMoveRight() = default;

  public:
	void Execute(GameObject *self, GameBase *game,
				 float deltaTime) override;
	static auto Instance() -> Command * {
		static CommandPhysicsMoveRight _instance;
		return &_instance;
	}
};

#endif
