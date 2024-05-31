#include "camera.h"
#include <iostream>

Camera::Camera(){ }

Camera::~Camera(){ }

void Camera::InitializeCamera(glm::vec3 position){
    this->position = position;
    this->target = glm::vec3{5.0f,0.0f,5.0f};
    this->up = glm::vec3{0.0f,1.0f,0.0f};
    this->fov = glm::radians(45.0);
    this->angle = glm::vec2(0,0);
    this->zoomLevel = 12.0f;
}

void Camera::Update(glm::vec3 targetPosition){    
    int x;
    int y;
    SDL_GetRelativeMouseState(&x,&y);
    
    angle += glm::vec2(glm::radians(f32(x)),glm::radians(f32(y)));

    if(angle.y > glm::radians(89.0f)){
        angle.y = glm::radians(89.0f);
    }
    if(angle.y < glm::radians(-89.0f)){
        angle.y = glm::radians(-89.0f);
    }

    target = targetPosition;
    position.x = glm::sin(angle.x) * zoomLevel * glm::cos(angle.y) + target.x;
    position.y = ((angle.y <= 0.0f)? 1 : -1) * glm::sin(angle.y) * zoomLevel * glm::sin(angle.y) + target.y;
    position.z = -glm::cos(angle.x) * zoomLevel * glm::cos(angle.y) + target.z;
}    

glm::mat4 Camera::GetViewProjectionMatrix(){
    glm::mat4 view = glm::lookAt(position, target, up);
    glm::mat4 projection = glm::perspective(fov, 1280.0f/720.0f, 0.01f, 1000.0f);
    return projection * view;
}

glm::vec3 Camera::GetPosition(){    
    return position;
}

glm::vec3 Camera::GetForward(){
    return forward;
}

glm::vec3 Camera::GetTarget(){
    return target;
}       

glm::vec3 Camera::GetRight(){
    return right;
}

glm::vec3 Camera::GetUp(){
    return up;
}

f32 Camera::GetFov(){
    return fov;
}