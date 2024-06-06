#include "bounding_box_component.h"
#include "game_object.h"

bool BoundingBoxComponent::collide(BoundingBoxComponent &other) {
	bool collision_x = (gameObject->position.x + origin.x) + size.x >=
	                       (other.gameObject->position.x + other.origin.x) &&
	                   (other.gameObject->position.x + other.origin.x) + other.size.x >=
	                       (gameObject->position.x + origin.x);
	bool collision_y = (gameObject->position.y + origin.y) + size.y >=
	                       (other.gameObject->position.y + other.origin.y) &&
	                   (other.gameObject->position.y + other.origin.y) + other.size.y >=
	                       (gameObject->position.y + origin.y);
	bool collision_z = (gameObject->position.z + origin.z) + size.z >=
	                       (other.gameObject->position.z + other.origin.z) &&
	                   (other.gameObject->position.z + other.origin.z) + other.size.z >=
	                       (gameObject->position.z + origin.z);

	return collision_x && collision_y && collision_z;
}
