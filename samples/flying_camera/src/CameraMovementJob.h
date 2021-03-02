#ifndef SMARTIN3D_CAMERAMOVEMENTJOB_H
#define SMARTIN3D_CAMERAMOVEMENTJOB_H

#include "base/App.h"

using namespace smartin;

class CameraMovementJob : public base::Job {
public:
    CameraMovementJob(std::shared_ptr<base::Camera> camera, float _speed, float _turnSpeed) {
        cameraTransform = camera->GetTransform();
        speed = _speed;
        turnSpeed = _turnSpeed;
    }

    void Tick() override {
        glm::vec3 forward = cameraTransform->GetForward();
        glm::vec3 right = cameraTransform->GetRight();
        glm::vec3 up = cameraTransform->GetUp();

        // Keys
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

        if (utils::input::keyboard::IsKey(KEY_W))
            direction += forward;
        if (utils::input::keyboard::IsKey(KEY_S))
            direction -= forward;

        if (utils::input::keyboard::IsKey(KEY_A))
            direction += right;
        if (utils::input::keyboard::IsKey(KEY_D))
            direction -= right;

        if (utils::input::keyboard::IsKey(KEY_R))
            direction += up;
        if (utils::input::keyboard::IsKey(KEY_F))
            direction -= up;

        if (direction != glm::vec3(0.0f, 0.0f, 0.0f)) {
            direction = utils::time::GetDeltaTime() * speed * glm::normalize(direction);
            cameraTransform->Move(direction);
        }

        // Mouse
        glm::vec2 mouseDelta = utils::input::mouse::GetCursorDelta();
        mouseDelta *= turnSpeed;

        float yaw = -mouseDelta.x;
        float pitch = mouseDelta.y;
        if (pitch > 89.0f)
            pitch = 89.0f;
        else if (pitch < -89.0f)
            pitch = -89.0f;

        cameraTransform->Rotate(glm::vec3(pitch, yaw, 0.0f));
    }

private:
    std::shared_ptr<base::Transform> cameraTransform;
    float speed, turnSpeed;
};


#endif //SMARTIN3D_CAMERAMOVEMENTJOB_H
