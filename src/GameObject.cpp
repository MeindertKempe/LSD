#include "draw_component.h"
#include "game_object.h"
#include "glm/gtc/matrix_transform.hpp"
#include <cstdio>

static int id_count = 0;

GameObject::GameObject(std::vector<GameObject *> *gameObjects) : gameObjects{ gameObjects } {
	id = id_count++;
}

GameObject::~GameObject() {}

void GameObject::AddComponent(Component *component) {
	component->SetGameObject(this);
	components.push_back(component);
}

void GameObject::AddDrawComponent(DrawComponent *drawComponent) {
	this->drawComponent = drawComponent;
}

void GameObject::AddBBComponent(BoundingBoxComponent *bbComponent) {
	this->boundingBoxComponent = bbComponent;
}

std::list<Component *> GameObject::GetComponents() { return components; }

DrawComponent *GameObject::GetDrawComponent() { return drawComponent; }

BoundingBoxComponent *GameObject::GetBBComponent() { return boundingBoxComponent; }

void GameObject::Draw(glm::mat4 projectionView) {
	if (!drawComponent) return;

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix           = glm::translate(modelMatrix, position);
	modelMatrix           = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix           = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix           = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
	modelMatrix           = glm::scale(modelMatrix, scale);

	drawComponent->Draw(projectionView, modelMatrix);

	if (boundingBoxComponent) {
		for (GameObject *gameObject : *gameObjects) {
			if (!gameObject->boundingBoxComponent) continue;
			if (gameObject->id == id) continue;
			if (boundingBoxComponent->collide(*gameObject->boundingBoxComponent)) {
				printf("collision between %i and %i\n", id, gameObject->id);
			}
		}
	}
}

void GameObject::Update(float elapsedTime) {
	for (auto &c : components) c->Update(elapsedTime);
}
