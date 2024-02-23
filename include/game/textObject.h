#ifndef TEXT_OBJECT
#define TEXT_OBJECT

#include "game/gameObject.h"

class TextObject : public GameObject {
  protected:
	std::string text;

  public:
	void SetObjectByYaml(const YAML::Node &object) override;
	void Update(float dt) override {}
};

#endif
