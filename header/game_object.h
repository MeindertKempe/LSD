#pragma once

#include "bounding_box_component.h"
#include "component.h"
#include "draw_component.h"
#include <glm/glm.hpp>
#include <list>
#include <vector>

class GameObject {
	int id;
	std::vector<GameObject *> *gameObjects;
	DrawComponent *drawComponent               = nullptr;
	BoundingBoxComponent *boundingBoxComponent = nullptr;
	std::list<Component *> components;

public:
	bool collides = false;
	void (*onCollision)(void);
	GameObject(std::vector<GameObject *> *gameObjects);
	~GameObject();

	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale    = glm::vec3(1, 1, 1);

	void AddComponent(Component *component);
	std::list<Component *> GetComponents();
	DrawComponent *GetDrawComponent();
	BoundingBoxComponent *GetBBComponent();
	void Update(float elapsedTime);
	void Draw(glm::mat4 projectioView);
	void AddDrawComponent(DrawComponent *drawComponent);
	float GetZ();
	void AddBBComponent(BoundingBoxComponent *bbComponent);

	template <class T> T *GetComponent() {
		for (auto c : components) {
			T *t = dynamic_cast<T *>(c);
			if (t) return t;
		}
		return nullptr;
	}

	template <class T> void RemoveComponent() {
		components.remove_if([](Component *c) {
			T *t = dynamic_cast<T *>(c);
			return t != nullptr;
		});
	}
};
