#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "game/gameObject.h"

#include <string>

class StaticObject : public GameObject {
	std::string onClickEvent;

  public:
	StaticObject() = default;
	~StaticObject() override = default;

	void SetObjectByYaml(const YAML::Node &object) override;

	[[nodiscard]] auto GetOnClickEvent() const
		-> std::string override {
		return this->onClickEvent;
	}
};

#endif
