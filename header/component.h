#pragma once
#include "dependencies.h"

class GameObject;

class Component {
protected:
	GameObject *gameObject;

public:
	Component();
	~Component();

	virtual void Update(f32 elapsedTime){};

	inline void SetGameObject(GameObject *gameObject) { this->gameObject = gameObject; }
};
