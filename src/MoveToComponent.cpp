#include "GameObject.h" //or whatever the gameobject header file will be called
#include "move_to_component.h"

MoveToComponent::MoveToComponent() {}

void MoveToComponent::update(float elapsedTime) {
	gameObject->position = (1 - speed) * gameObject->position + speed * target;
}
