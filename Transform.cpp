#include "Transform.h"

smartin::base::Transform::Transform(glm::vec3 _position, glm::vec3 _size, glm::vec3 _rotation) {
    position = _position;
    size = _size;
    rotation = _rotation;
}

void smartin::base::Transform::SetPosition(glm::vec3 _position) {
    position = _position;
}

void smartin::base::Transform::Move(glm::vec3 direction) {
    SetPosition(position + direction);
}

void smartin::base::Transform::SetSize(glm::vec3 _size) {
    size = _size;
}

void smartin::base::Transform::Scale(glm::vec3 scale) {
    SetSize(size * scale);
}

void smartin::base::Transform::Scale(GLfloat scale) {
    SetSize(size * scale);
}

void smartin::base::Transform::SetRotation(glm::vec3 _rotation) {
    rotation = _rotation;
}

void smartin::base::Transform::Rotate(glm::vec3 axis, float angle) {
    glm::mat4 rot(1.0f);
    rot = glm::rotate(rot, glm::radians(angle), axis);
    modelMatrix *= rot;
    // TODO: Update rotation
}

smartin::base::Transform::~Transform() {

}

void smartin::base::Transform::Update() {
    glm::mat4 mat(1.0f);

    // Move
    mat = glm::translate(mat, position);

    // Scale
    mat = glm::scale(mat, size);

    // Rotate
    mat = glm::rotate(mat, glm::radians(rotation.x), RIGHT);
    mat = glm::rotate(mat, glm::radians(rotation.y), UP);
    mat = glm::rotate(mat, glm::radians(rotation.z), FORWARD);

    modelMatrix = mat;
}

// Axes
glm::vec3 smartin::base::Transform::RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 smartin::base::Transform::UP = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 smartin::base::Transform::FORWARD = glm::vec3(0.0f, 0.0f, 1.0f);
