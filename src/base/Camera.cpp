#include "base/Camera.h"

const float smartin::base::Camera::Camera::DEFAULT_FIELD_OF_VIEW = 45.0f;
const float smartin::base::Camera::Camera::DEFAULT_NEAR_PLANE = 0.1f;
const float smartin::base::Camera::Camera::DEFAULT_FAR_PLANE = 100.0f;
const float smartin::base::Camera::Camera::DEFAULT_ASPECT_RATIO = 16.0f / 9.0f;

smartin::base::Camera::Camera(std::shared_ptr<Transform> transform) :
    Actor(transform),
    fieldOfView(DEFAULT_FIELD_OF_VIEW),
    nearPlane(DEFAULT_NEAR_PLANE),
    farPlane(DEFAULT_FAR_PLANE),
    aspect(DEFAULT_ASPECT_RATIO) { }

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
