
#ifndef ADAPTER_H
#define ADAPTER_H

#include <cstring>
#include <list>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

#include "resource_manager.h"
#include "sprite_renderer.h"

class Adapter {
  private:
	int width, height;
	bool keys[1024];
	bool buttons[1024];
	SpriteRenderer *renderer;
	using EventType =
		std::tuple<int, bool, std::pair<double, double>>;
	std::queue<EventType, std::list<EventType>> mouseEvents;

  public:
	~Adapter() { delete renderer; }

	void Init(int Width, int Height);

	void SetKeyPress(int key) { keys[key] = true; }
	void SetKeyUnPress(int key) { keys[key] = false; }
	[[nodiscard]] auto GetKeyState(int key) const -> bool {
		return keys[key];
	}
	void SetMouseButtonPress(int button, double x, double y) {
		buttons[button] = true;
		mouseEvents.emplace(button, true, std::make_pair(x, y));
	}
	void SetMouseButtonUnPress(int button, double x, double y) {
		buttons[button] = false;
		mouseEvents.emplace(button, false, std::make_pair(x, y));
	}
	[[nodiscard]] auto GetMouseButtonState(int button) const
		-> bool {
		return buttons[button];
	}
	auto GetNextMouseEvent() -> EventType {
		if (mouseEvents.empty()) {
			return {-1, false, {0, 0}};
		}
		auto tmp = mouseEvents.front();
		mouseEvents.pop();
		return tmp;
	}

	void Draw(const char *spriteId, float posx, float posy,
			  float width, float height, float rotation = 0.0F,
			  float colorR = 1.0F, float colorG = 1.0F,
			  float colorB = 1.0F);
};

#endif
