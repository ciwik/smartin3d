#include "base/Transform.h"

smartin::base::Transform::Transform(const glm::vec3& _position, const glm::vec3& _size, const glm::vec3& _eulerAngles) :
    position(_position),
    size(_size),
    rotation(glm::quat(_eulerAngles))
{
    Update();
}

smartin::base::Transform::Transform(const glm::vec3& _position, const glm::vec3& _size, const glm::quat& _rotation) :
    position(_position),
    size(_size),
    rotation(_rotation)
{
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

void smartin::base::Transform::Move(const glm::vec3& direction) {
    position += direction;
}

void smartin::base::Transform::SetPosition(const glm::vec3& _position) {
    position = _position;
}

void smartin::base::Transform::Scale(const glm::vec3& scale) {
    size *= scale;
}

void smartin::base::Transform::Scale(GLfloat scale) {
    size *= scale;
}

void smartin::base::Transform::Rotate(const glm::quat& additionalRotation) {
    rotation *= additionalRotation;
}

void smartin::base::Transform::RotateAround(const glm::vec3& axis, GLfloat angle) {
    float a = glm::radians(angle) / 2;
    glm::quat q = glm::quat(cos(a), axis.x * sin(a), axis.y * sin(a), axis.z * sin(a));
    rotation *= q;
}

glm::quat EulerAnglesToQuaternion(const glm::vec3& eulerAngles) {
    float pitch = glm::radians(eulerAngles.x);
    float yaw = glm::radians(eulerAngles.y);
    float roll = glm::radians(eulerAngles.z);

    glm::quat q = glm::quat(glm::vec3(pitch, yaw, roll));
    q = glm::normalize(q);

    return q;
}

void smartin::base::Transform::Rotate(const glm::vec3& eulerAngles) {
    glm::quat q = EulerAnglesToQuaternion(eulerAngles);
    Rotate(q);
}

void smartin::base::Transform::SetRotation(const glm::vec3& eulerAngles) {
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
glm::vec3 smartin::base::Transform::rightAxis = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 smartin::base::Transform::upAxis = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 smartin::base::Transform::forwardAxis = glm::vec3(0.0f, 0.0f, 1.0f);
