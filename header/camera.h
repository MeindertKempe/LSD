#pragma once
#include "SDL.h"
#include "dependencies.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

// Third person camera class
class Camera {
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 worldUp;
	glm::vec3 right;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 moveDirection;
	glm::vec2 lastMouse;
	glm::vec2 angle;
	f32 fov;
	f32 yaw;
	f32 pitch;
	f32 zoomLevel;

public:
	Camera();
	~Camera();
	void InitializeCamera(glm::vec3 position);
	void Update(glm::vec3 targetPosition);
	glm::mat4 GetViewProjectionMatrix();
	glm::vec3 GetPosition();
	glm::vec3 GetTarget();
	glm::vec3 GetRight();
	glm::vec3 GetForward();
	glm::vec3 GetUp();
	f32 GetFov();
};
