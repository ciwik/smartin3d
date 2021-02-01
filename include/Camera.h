#ifndef SMARTIN3D_CAMERA_H
#define SMARTIN3D_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Actor.h"

namespace smartin::base {
    class Camera : public Actor {
    public:
        Camera(Transform* transform = new Transform()) : Actor(transform) { }

        void Update() override;

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();

        GLfloat fieldOfView = 60.0f;
        GLfloat nearPlane = 0.1f;
        GLfloat farPlane = 100.0f;
        GLfloat aspect = 1.77777777778f; // 16:9

        ~Camera();
    };
}

#endif //SMARTIN3D_CAMERA_H
