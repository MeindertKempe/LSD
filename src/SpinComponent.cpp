#include "spin_component.h"
#include "game_object.h"


SpinComponent::SpinComponent(float speed)
{
	this->speed = speed;
}


SpinComponent::~SpinComponent()
{
}

void SpinComponent::Update(float elapsedTime)
{
	gameObject->rotation.y += elapsedTime * speed;
}
