#include "bounding_box_component.h"
#include "game_object.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

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

void BoundingBoxComponent::Draw(glm::mat4 projectionView, glm::mat4 transform) {
#ifndef DEBUG
	return;
#endif
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projectionView));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(transform));

	glm::vec3 minBounds = origin;
	glm::vec3 maxBounds = origin + size;

	glm::vec3 corners[8] = { minBounds,
		                     minBounds + glm::vec3(maxBounds.x, 0.0f, 0.0f),
		                     minBounds + glm::vec3(maxBounds.x, 0.0f, maxBounds.z),
		                     minBounds + glm::vec3(0.0f, 0.0f, maxBounds.z),
		                     minBounds + glm::vec3(0.0f, maxBounds.y, 0.0f),
		                     minBounds + glm::vec3(maxBounds.x, maxBounds.y, 0.0f),
		                     minBounds + glm::vec3(maxBounds.x, maxBounds.y, maxBounds.z),
		                     minBounds + glm::vec3(0.0f, maxBounds.y, maxBounds.z) };

	glBegin(GL_LINES);

	// Draw lines between corners to form the edges of the box
	for (int i = 0; i < 4; ++i) {
		// Bottom face
		glVertex3f(corners[i].x, corners[i].y, corners[i].z);
		glVertex3f(corners[(i + 1) % 4].x, corners[(i + 1) % 4].y, corners[(i + 1) % 4].z);

		// Top face
		glVertex3f(corners[i + 4].x, corners[i + 4].y, corners[i + 4].z);
		glVertex3f(corners[((i + 1) % 4) + 4].x, corners[((i + 1) % 4) + 4].y,
		           corners[((i + 1) % 4) + 4].z);

		// Connections between top and bottom faces
		glVertex3f(corners[i].x, corners[i].y, corners[i].z);
		glVertex3f(corners[i + 4].x, corners[i + 4].y, corners[i + 4].z);
	}
	glEnd();
}