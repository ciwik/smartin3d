#include "base/Camera.h"

const float smartin::base::Camera::Camera::defaultFieldOfView = 45.0f;
const float smartin::base::Camera::Camera::defaultNearPlane = 0.1f;
const float smartin::base::Camera::Camera::defaultFarPlane = 100.0f;
const float smartin::base::Camera::Camera::defaultAspectRatio = 16.0f / 9.0f;

smartin::base::Camera::Camera(std::shared_ptr<Transform> transform) :
    Actor(transform),
    fieldOfView(defaultFieldOfView),
    nearPlane(defaultNearPlane),
    farPlane(defaultFarPlane),
    aspect(defaultAspectRatio) { }

void smartin::base::Camera::Update() {
    Actor::Update();
}

glm::mat4 smartin::base::Camera::GetViewMatrix() const {
    glm::vec3 position = transform->GetPosition();
    glm::vec3 forward = transform->GetForward();
    glm::vec3 up = transform->GetUp();
    return glm::lookAt(position, position + forward, up);
}

glm::mat4 smartin::base::Camera::GetProjectionMatrix() const {
    return glm::perspective(fieldOfView, aspect, nearPlane, farPlane);
}

smartin::base::Camera::~Camera() { }
