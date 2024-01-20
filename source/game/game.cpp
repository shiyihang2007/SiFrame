#include "game/game.h"
#include "resource_manager.h"

void GameProject::CleanUp() {
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
}
