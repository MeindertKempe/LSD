#include "game_object.h"
#include "spin_component.h"

SpinComponent::SpinComponent(f32 speed) { this->speed = speed; }

SpinComponent::~SpinComponent() {}

void SpinComponent::Update(f32 elapsedTime) { gameObject->rotation.y += elapsedTime * speed; }
