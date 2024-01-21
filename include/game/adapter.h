
#ifndef ADAPTER_H
#define ADAPTER_H

#include <cstring>

#include "resource_manager.h"
#include "sprite_renderer.h"

class Adapter {
  private:
	int width, height;
	bool keys[1024];
	SpriteRenderer *renderer;

  public:
	~Adapter() { delete renderer; }

	void Init(int Width, int Height);

	void SetKeyPress(int key) { keys[key] = true; }
	void SetKeyUnPress(int key) { keys[key] = false; }
	[[nodiscard]] auto GetKeyState(int key) const -> bool {
		return keys[key];
	}

	void Draw(const char *spriteId, float posx, float posy,
			  float width, float height, float rotation = 0.0F,
			  float colorR = 1.0F, float colorG = 1.0F,
			  float colorB = 1.0F);

	void LoadTexture(const char *textureId, bool alpha,
					 const char *filePath);
};

#endif
