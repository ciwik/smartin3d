#ifndef SMARTIN3D_CAMERA_H
#define SMARTIN3D_CAMERA_H

#include "precompiled.h"

#include "base/Actor.h"

namespace smartin::base {
    class Camera : public Actor {
    public:
        Camera(std::shared_ptr<Transform> transform = std::make_shared<Transform>());

        void Update() override;

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        float fieldOfView, nearPlane, farPlane, aspect;

        ~Camera();

    private:
        static const float DEFAULT_FIELD_OF_VIEW;
        static const float DEFAULT_NEAR_PLANE;
        static const float DEFAULT_FAR_PLANE;
        static const float DEFAULT_ASPECT_RATIO;
    };
}

#endif //SMARTIN3D_CAMERA_H
