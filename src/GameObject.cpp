#include "draw_component.h"
#include "game_object.h"
#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject() {}

GameObject::~GameObject() {}

void GameObject::AddComponent(Component *component) {
	component->SetGameObject(this);
	components.push_back(component);
}

void GameObject::AddDrawComponent(DrawComponent *drawComponent) {
	this->drawComponent = drawComponent;
}

std::list<Component *> GameObject::GetComponents() { return components; }

void GameObject::Draw(glm::mat4 projectionView) {
	if (!drawComponent) return;

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix           = glm::translate(modelMatrix, position);
	modelMatrix           = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix           = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix           = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
	modelMatrix           = glm::scale(modelMatrix, scale);

	drawComponent->Draw(projectionView, modelMatrix);
}

void GameObject::Update(float elapsedTime) {
	for (auto &c : components) c->Update(elapsedTime);
}