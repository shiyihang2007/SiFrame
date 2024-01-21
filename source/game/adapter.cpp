#include "game/adapter.h"
#include "resource_manager.h"

void Adapter::Init(int Width, int Height) {
	this->width = Width;
	this->height = Height;
	// load shaders
	ResourceManager::LoadShader("./shader/sprite.vert",
								"./shader/sprite.frag", nullptr,
								"sprite");
	// configure shaders
	glm::mat4 projection =
		glm::ortho(0.0F, static_cast<float>(Width),
				   static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image",
														  0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection",
													projection);
	// set render-specific controls
	renderer =
		new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Adapter::Draw(const char *spriteId, float posx, float posy,
				   float width, float height, float rotation,
				   float colorR, float colorG, float colorB) {
	renderer->DrawSprite(
		ResourceManager::GetTexture(spriteId),
		{posx * 0.01F * this->width, posy * 0.01F * this->height},
		{width * 0.01F * this->width, height * 0.01F * this->height},
		rotation, {colorR, colorG, colorB});
}
