#include "Transform.h"

smartin::base::Transform::Transform(glm::vec3 _position, glm::vec3 _size, glm::vec3 _eulerAngles) {
    position = _position;
    size = _size;
    rotation = glm::quat(_eulerAngles);

    Update();
}

smartin::base::Transform::Transform(glm::vec3 _position, glm::vec3 _size, glm::quat _rotation) {
    position = _position;
    size = _size;
    rotation = _rotation;

    Update();
}

glm::vec3 smartin::base::Transform::GetEulerAngles() const {
    GLfloat t0 = 2.0f * (rotation.w * rotation.x + rotation.y * rotation.z);
    GLfloat t1 = 1.0f - 2.0f * (rotation.x * rotation.x + rotation.y * rotation.y);
    GLfloat roll = atan2(t0, t1);

    GLfloat t2 = 2.0f * (rotation.w * rotation.y - rotation.z * rotation.x);
    t2 = t2 > 1.0f ? 1.0f : t2;
    t2 = t2 < -1.0f ? 1.0f : t2;
    GLfloat pitch = asin(t2);

    GLfloat t3 = 2.0f * (rotation.w * rotation.z + rotation.x * rotation.y);
    GLfloat t4 = 1.0f - 2.0f * (rotation.y * rotation.y + rotation.z * rotation.z);
    GLfloat yaw = atan2(t3, t4);

    return glm::vec3(glm::degrees(roll), glm::degrees(pitch), glm::degrees(yaw));
}

void smartin::base::Transform::Move(glm::vec3 direction) {
    position += direction;
}

void smartin::base::Transform::Scale(glm::vec3 scale) {
    size *= scale;
}

void smartin::base::Transform::Scale(GLfloat scale) {
    size *= scale;
}

void smartin::base::Transform::Rotate(glm::quat additionalRotation) {
    rotation *= additionalRotation;
}

void smartin::base::Transform::RotateAround(glm::vec3 axis, GLfloat angle) {
    float a = glm::radians(angle) / 2;
    glm::quat q = glm::quat(cos(a), axis.x * sin(a), axis.y * sin(a), axis.z * sin(a));
    rotation *= q;
}

glm::quat EulerAnglesToQuaternion(glm::vec3 eulerAngles) {
    float pitch = glm::radians(eulerAngles.x) / 2.0f;
    float yaw = glm::radians(eulerAngles.y) / 2.0f;
    float roll = glm::radians(eulerAngles.z) / 2.0f;

    glm::quat q = glm::quat();
    q.x = sin(roll) * cos(pitch) * cos(yaw) - cos(roll) * sin(pitch) * sin(yaw);
    q.y = cos(roll) * sin(pitch) * cos(yaw) + sin(roll) * cos(pitch) * sin(yaw);
    q.z = cos(roll) * cos(pitch) * sin(yaw) - sin(roll) * sin(pitch) * cos(yaw);
    q.w = cos(roll) * cos(pitch) * cos(yaw) + sin(roll) * sin(pitch) * sin(yaw);

    return q;
}

void smartin::base::Transform::Rotate(glm::vec3 eulerAngles) {
    glm::quat q = EulerAnglesToQuaternion(eulerAngles);
    Rotate(q);
}

void smartin::base::Transform::SetRotation(glm::vec3 eulerAngles) {
    glm::quat q = EulerAnglesToQuaternion(eulerAngles);
    rotation = q;
}

void smartin::base::Transform::Update() {
    glm::mat4 mat(1.0f);

    // Move
    mat = glm::translate(mat, position);

    // Scale
    mat = glm::scale(mat, size);

    // Rotate
    glm::mat4 rot = glm::toMat4(rotation);
    mat *= rot;

    modelMatrix = mat;
}

smartin::base::Transform::~Transform() {

}

// Axes
glm::vec3 smartin::base::Transform::RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 smartin::base::Transform::UP = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 smartin::base::Transform::FORWARD = glm::vec3(0.0f, 0.0f, 1.0f);
