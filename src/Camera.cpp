#include "Camera.h"

void smartin::base::Camera::Update() {
    Actor::Update();
}

glm::mat4 smartin::base::Camera::GetViewMatrix() {
    return glm::mat4();     // TODO
}

glm::mat4 smartin::base::Camera::GetProjectionMatrix() {
    return glm::mat4();     // TODO
}

smartin::base::Camera::~Camera() {

}
