#pragma once

#include "bounding_box_component.h"
#include "component.h"
#include "draw_component.h"
#include <glm/glm.hpp>
#include <list>
#include <vector>

class GameObject {
	std::vector<GameObject *> *gameObjects;
	std::list<DrawComponent *> drawComponents;
	BoundingBoxComponent *boundingBoxComponent = nullptr;
	std::list<Component *> components;

public:
	int id, score;
	bool collides = false;
	void (*onCollision)(GameObject &gameObject) = nullptr;
	GameObject(std::vector<GameObject *> *gameObjects, int score = 0);
	~GameObject();

	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale    = glm::vec3(1, 1, 1);

	void AddComponent(Component *component);
	std::list<Component *> GetComponents();
	std::list<DrawComponent *> GetDrawComponents();
	BoundingBoxComponent *GetBBComponent();
	void Update(float elapsedTime);
	void Draw(glm::mat4 projectioView);
	void AddDrawComponent(DrawComponent *drawComponent);
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
