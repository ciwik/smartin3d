#include "base/Camera.h"

smartin::base::Camera::Camera(std::shared_ptr<Transform> transform) : Actor(transform) {
    fieldOfView = 45.0f;
    nearPlane = 0.1f;
    farPlane = 100.0f;
    aspect = 16.0f / 9.0f;
}

void smartin::base::Camera::Update() {
    Actor::Update();
}

glm::mat4 smartin::base::Camera::GetViewMatrix() {
    glm::vec3 position = transform->GetPosition();
    glm::vec3 forward = transform->GetForward();
    glm::vec3 up = transform->GetUp();
    return glm::lookAt(position, position + forward, up);
}

glm::mat4 smartin::base::Camera::GetProjectionMatrix() {
    return glm::perspective(fieldOfView, aspect, nearPlane, farPlane);
}

smartin::base::Camera::~Camera() { }
