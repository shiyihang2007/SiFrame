#include "game/adapter.h"
#include "GLFW/glfw3.h"
#include "resource_manager.h"
#include "spdlog/spdlog.h"

void setKeyStrings(std::map<std::string, int> &keyStringMap);

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

	// set key string
	setKeyStrings(keyStringMap);

	// clear keys
	for (int i = 0; i < 1024; i++) {
		keys[i] = false;
		buttons[i] = false;
	}
}

void Adapter::Draw(const char *spriteId, float posx, float posy,
				   float width, float height, float rotation,
				   float colorR, float colorG, float colorB) {
	constexpr float SCALE = 0.01F;
	renderer->DrawSprite(ResourceManager::GetTexture(spriteId),
						 {posx, posy}, {width, height}, rotation,
						 {colorR, colorG, colorB});

	// spdlog::debug("draw sprite: {}, pos: ({}, {}), size: ({}, {}),
	// " 			  "rotation: {}, color: ({}, {}, {})",
	// spriteId, posx * SCALE
	// * static_cast<float>(this->width), 			  posy * SCALE *
	// static_cast<float>(this->height), 			  width * SCALE *
	// static_cast<float>(this->width), 			  height * SCALE
	// * static_cast<float>(this->height), 			  rotation,
	// colorR, colorG, colorB);
}

void setKeyStrings(std::map<std::string, int> &keyStringMap) {
	// control keys
	keyStringMap["escape"] = GLFW_KEY_ESCAPE;
	keyStringMap["F1"] = GLFW_KEY_F1;
	keyStringMap["F2"] = GLFW_KEY_F2;
	keyStringMap["F3"] = GLFW_KEY_F3;
	keyStringMap["F4"] = GLFW_KEY_F4;
	keyStringMap["F5"] = GLFW_KEY_F5;
	keyStringMap["F6"] = GLFW_KEY_F6;
	keyStringMap["F7"] = GLFW_KEY_F7;
	keyStringMap["F8"] = GLFW_KEY_F8;
	keyStringMap["F9"] = GLFW_KEY_F9;
	keyStringMap["F10"] = GLFW_KEY_F10;
	keyStringMap["F11"] = GLFW_KEY_F11;
	keyStringMap["F12"] = GLFW_KEY_F12;

	// main keys
	keyStringMap["`"] = GLFW_KEY_GRAVE_ACCENT;
	keyStringMap["1"] = GLFW_KEY_1;
	keyStringMap["2"] = GLFW_KEY_2;
	keyStringMap["3"] = GLFW_KEY_3;
	keyStringMap["4"] = GLFW_KEY_4;
	keyStringMap["5"] = GLFW_KEY_5;
	keyStringMap["6"] = GLFW_KEY_6;
	keyStringMap["7"] = GLFW_KEY_7;
	keyStringMap["8"] = GLFW_KEY_8;
	keyStringMap["9"] = GLFW_KEY_9;
	keyStringMap["0"] = GLFW_KEY_0;
	keyStringMap["-"] = GLFW_KEY_MINUS;
	keyStringMap["="] = GLFW_KEY_EQUAL;
	keyStringMap["backspace"] = GLFW_KEY_BACKSPACE;
	keyStringMap["tab"] = GLFW_KEY_TAB;
	keyStringMap["q"] = GLFW_KEY_Q, keyStringMap["Q"] = GLFW_KEY_Q;
	keyStringMap["w"] = GLFW_KEY_W, keyStringMap["W"] = GLFW_KEY_W;
	keyStringMap["e"] = GLFW_KEY_E, keyStringMap["E"] = GLFW_KEY_E;
	keyStringMap["r"] = GLFW_KEY_R, keyStringMap["R"] = GLFW_KEY_R;
	keyStringMap["t"] = GLFW_KEY_T, keyStringMap["T"] = GLFW_KEY_T;
	keyStringMap["y"] = GLFW_KEY_Y, keyStringMap["Y"] = GLFW_KEY_Y;
	keyStringMap["u"] = GLFW_KEY_U, keyStringMap["U"] = GLFW_KEY_U;
	keyStringMap["i"] = GLFW_KEY_I, keyStringMap["I"] = GLFW_KEY_I;
	keyStringMap["o"] = GLFW_KEY_O, keyStringMap["O"] = GLFW_KEY_O;
	keyStringMap["p"] = GLFW_KEY_P, keyStringMap["P"] = GLFW_KEY_P;
	keyStringMap["["] = GLFW_KEY_LEFT_BRACKET;
	keyStringMap["]"] = GLFW_KEY_RIGHT_BRACKET;
	keyStringMap["\\"] = GLFW_KEY_BACKSLASH;
	keyStringMap["a"] = GLFW_KEY_A, keyStringMap["A"] = GLFW_KEY_A;
	keyStringMap["s"] = GLFW_KEY_S, keyStringMap["S"] = GLFW_KEY_S;
	keyStringMap["d"] = GLFW_KEY_D, keyStringMap["D"] = GLFW_KEY_D;
	keyStringMap["f"] = GLFW_KEY_F, keyStringMap["F"] = GLFW_KEY_F;
	keyStringMap["g"] = GLFW_KEY_G, keyStringMap["G"] = GLFW_KEY_G;
	keyStringMap["h"] = GLFW_KEY_H, keyStringMap["H"] = GLFW_KEY_H;
	keyStringMap["j"] = GLFW_KEY_J, keyStringMap["J"] = GLFW_KEY_J;
	keyStringMap["k"] = GLFW_KEY_K, keyStringMap["K"] = GLFW_KEY_K;
	keyStringMap["l"] = GLFW_KEY_L, keyStringMap["L"] = GLFW_KEY_L;
	keyStringMap[";"] = GLFW_KEY_SEMICOLON;
	keyStringMap["'"] = GLFW_KEY_APOSTROPHE;
	keyStringMap["enter"] = GLFW_KEY_ENTER;
	keyStringMap["lshift"] = GLFW_KEY_LEFT_SHIFT;
	keyStringMap["z"] = GLFW_KEY_Z, keyStringMap["Z"] = GLFW_KEY_Z;
	keyStringMap["x"] = GLFW_KEY_X, keyStringMap["X"] = GLFW_KEY_X;
	keyStringMap["c"] = GLFW_KEY_C, keyStringMap["C"] = GLFW_KEY_C;
	keyStringMap["v"] = GLFW_KEY_V, keyStringMap["V"] = GLFW_KEY_V;
	keyStringMap["b"] = GLFW_KEY_B, keyStringMap["B"] = GLFW_KEY_B;
	keyStringMap["n"] = GLFW_KEY_N, keyStringMap["N"] = GLFW_KEY_N;
	keyStringMap["m"] = GLFW_KEY_M, keyStringMap["M"] = GLFW_KEY_M;
	keyStringMap[","] = GLFW_KEY_COMMA;
	keyStringMap["."] = GLFW_KEY_PERIOD;
	keyStringMap["/"] = GLFW_KEY_SLASH;
	keyStringMap["rshift"] = GLFW_KEY_RIGHT_SHIFT;
	keyStringMap["lctrl"] = GLFW_KEY_LEFT_CONTROL;
	keyStringMap["lalt"] = GLFW_KEY_LEFT_ALT;
	keyStringMap["space"] = GLFW_KEY_SPACE;
	keyStringMap["ralt"] = GLFW_KEY_RIGHT_ALT;
	keyStringMap["rctrl"] = GLFW_KEY_RIGHT_CONTROL;

	// editor keys
	keyStringMap["insert"] = GLFW_KEY_INSERT;
	keyStringMap["delete"] = GLFW_KEY_DELETE;
	keyStringMap["home"] = GLFW_KEY_HOME;
	keyStringMap["end"] = GLFW_KEY_END;
	keyStringMap["pageup"] = GLFW_KEY_PAGE_UP;
	keyStringMap["pagedown"] = GLFW_KEY_PAGE_DOWN;

	// way keys
	keyStringMap["up"] = GLFW_KEY_UP;
	keyStringMap["down"] = GLFW_KEY_DOWN;
	keyStringMap["left"] = GLFW_KEY_LEFT;
	keyStringMap["right"] = GLFW_KEY_RIGHT;

	// keypad keys
	keyStringMap["num0"] = GLFW_KEY_KP_0;
	keyStringMap["num1"] = GLFW_KEY_KP_1;
	keyStringMap["num2"] = GLFW_KEY_KP_2;
	keyStringMap["num3"] = GLFW_KEY_KP_3;
	keyStringMap["num4"] = GLFW_KEY_KP_4;
	keyStringMap["num5"] = GLFW_KEY_KP_5;
	keyStringMap["num6"] = GLFW_KEY_KP_6;
	keyStringMap["num7"] = GLFW_KEY_KP_7;
	keyStringMap["num8"] = GLFW_KEY_KP_8;
	keyStringMap["num9"] = GLFW_KEY_KP_9;
	keyStringMap["numenter"] = GLFW_KEY_KP_ENTER;
	keyStringMap["numadd"] = GLFW_KEY_KP_ADD;
	keyStringMap["numsub"] = GLFW_KEY_KP_SUBTRACT;
	keyStringMap["nummul"] = GLFW_KEY_KP_MULTIPLY;
	keyStringMap["numdiv"] = GLFW_KEY_KP_DIVIDE;
}
