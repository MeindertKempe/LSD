#pragma once

#include <glm/glm.hpp>
#include <list>

class Component;
class DrawComponent;
class BoundingBoxComponent;

class GameObject {
	DrawComponent *drawComponent = nullptr;
	std::list<Component *> components;

public:
	GameObject();
	~GameObject();

	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale    = glm::vec3(1, 1, 1);

	void AddComponent(Component *component);
	std::list<Component *> GetComponents();
	void Update(float elapsedTime);
	void Draw(glm::mat4 projectioView);
	void AddDrawComponent(DrawComponent *drawComponent);

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
