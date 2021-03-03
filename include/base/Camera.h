#ifndef SMARTIN3D_CAMERA_H
#define SMARTIN3D_CAMERA_H

#include "precompiled.h"

#include "base/Actor.h"

namespace smartin::base {
    class Camera : public Actor {
    public:
        Camera(std::shared_ptr<Transform> transform = std::make_shared<Transform>());

        void Update() override;

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();

        float fieldOfView, nearPlane, farPlane, aspect;

        ~Camera();
    };
}

#endif //SMARTIN3D_CAMERA_H
