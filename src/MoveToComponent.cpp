#include "game_object.h"
#include "move_to_component.h"
#include <iostream>

MoveToComponent::MoveToComponent(glm::vec3 *position) { target = *position; }

MoveToComponent::~MoveToComponent() {}

void MoveToComponent::Update(f32 elapsedTime) {
	gameObject->position = (1 - speed) * gameObject->position + speed * target;
	target.z            -= 0.02;
}
