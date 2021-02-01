#include "Camera.h"

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

smartin::base::Camera::~Camera() {

}
