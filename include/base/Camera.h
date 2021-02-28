#ifndef SMARTIN3D_CAMERA_H
#define SMARTIN3D_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "base/Actor.h"

namespace smartin::base {
    class Camera : public Actor {
    public:
        Camera(std::shared_ptr<Transform> transform = std::make_shared<Transform>()) : Actor(transform) { }

        void Update() override;

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();

        float fieldOfView = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;
        float aspect = 1.77777779f; // 16:9

        ~Camera();
    };
}

#endif //SMARTIN3D_CAMERA_H
