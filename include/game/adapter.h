
#ifndef ADAPTER_H
#define ADAPTER_H

#include <cstring>

#include "resource_manager.h"
#include "sprite_renderer.h"

class Adapter {
	bool Keys[1024];
	SpriteRenderer *renderer;

  public:
	~Adapter() { delete renderer; }

	void Init(int Width, int Height) {
		// load shaders
		ResourceManager::LoadShader("./shader/sprite.vert",
									"./shader/sprite.frag", nullptr,
									"sprite");
		// configure shaders
		glm::mat4 projection = glm::ortho(
			0.0F, static_cast<float>(Width),
			static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
		ResourceManager::GetShader("sprite").Use().SetInteger(
			"image", 0);
		ResourceManager::GetShader("sprite").SetMatrix4("projection",
														projection);
		// set render-specific controls
		renderer =
			new SpriteRenderer(ResourceManager::GetShader("sprite"));
	}

	void SetKeyPress(int key) { Keys[key] = true; }
	void SetKeyUnPress(int key) { Keys[key] = false; }
	[[nodiscard]] auto GetKeyState(int key) const -> bool {
		return Keys[key];
	}

	auto GetSpriteRenderer() -> SpriteRenderer * { return renderer; }
};

#endif
