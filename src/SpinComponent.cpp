#include "game_object.h"
#include "spin_component.h"

SpinComponent::SpinComponent(float speed) { this->speed = speed; }

SpinComponent::~SpinComponent() {}

void SpinComponent::Update(float elapsedTime) { gameObject->rotation.y += elapsedTime * speed; }
