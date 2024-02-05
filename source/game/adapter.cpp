#include "game/adapter.h"
#include "resource_manager.h"
#include "spdlog/spdlog.h"

void Adapter::Init(int Width, int Height) {
	spdlog::info("Initializing adapter");
	this->width = Width;
	this->height = Height;
	// load shaders
	ResourceManager::LoadShader("./shader/sprite.vert",
								"./shader/sprite.frag", nullptr,
								"sprite");
	// configure shaders
	glm::mat4 projection =
		glm::ortho(0.0F, static_cast<float>(Width),
				   static_cast<float>(Height), 0.0F, -1.0F, 1.0F);
	ResourceManager::GetShader("sprite").Use().SetInteger("image",
														  0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection",
													projection);
	// set render-specific controls
	renderer =
		new SpriteRenderer(ResourceManager::GetShader("sprite"));
	spdlog::info("Adapter inited.");
}

void Adapter::Draw(const char *spriteId, float posx, float posy,
				   float width, float height, float rotation,
				   float colorR, float colorG, float colorB) {
	constexpr float SCALE = 0.01F;
	renderer->DrawSprite(ResourceManager::GetTexture(spriteId),
						 {posx, posy}, {width, height}, rotation,
						 {colorR, colorG, colorB});

	// spdlog::debug("draw sprite: {}, pos: ({}, {}), size: ({}, {}),
	// " 			  "rotation: {}, color: ({}, {}, {})", 			  spriteId,
	// posx * SCALE
	// * static_cast<float>(this->width), 			  posy * SCALE *
	// static_cast<float>(this->height), 			  width * SCALE *
	// static_cast<float>(this->width), 			  height * SCALE
	// * static_cast<float>(this->height), 			  rotation,
	// colorR, colorG, colorB);
}
