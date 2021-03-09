#ifndef SMARTIN3D_CAMERA_H
#define SMARTIN3D_CAMERA_H

#include "precompiled.h"

#include "base/Actor.h"

namespace smartin::base {
    class Camera : public Actor {
    public:
        explicit Camera(std::shared_ptr<Transform> transform = std::make_shared<Transform>());

        void Update() override;

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        float fieldOfView, nearPlane, farPlane, aspect;

        ~Camera();

    private:
        static const float defaultFieldOfView;
        static const float defaultNearPlane;
        static const float defaultFarPlane;
        static const float defaultAspectRatio;
    };
}

#endif //SMARTIN3D_CAMERA_H
