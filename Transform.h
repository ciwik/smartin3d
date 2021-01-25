#ifndef SMARTIN3D_TRANSFORM_H
#define SMARTIN3D_TRANSFORM_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace smartin::base {
    class Transform {
    public:
        Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
                  glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));

        glm::vec3 GetPosition() const { return position; }
        glm::vec3 GetSize() const { return size; }
        glm::vec3 GetRotation() const { return rotation; }
        glm::mat4 GetModelMatrix() const { return modelMatrix; }

        glm::vec3 GetForward();             // TODO
        glm::vec3 GetRight();               // TODO
        glm::vec3 GetUp();                  // TODO

        void Update();

        void SetPosition(glm::vec3 position);
        void Move(glm::vec3 direction);

        void SetSize(glm::vec3 size);
        void Scale(glm::vec3 scale);
        void Scale(GLfloat scale);

        void SetRotation(glm::vec3 rotation);
        void Rotate(glm::vec3 axis, float angle);

        ~Transform();

    private:
        // TODO: Use quaternion for rotation
        glm::vec3 position, size, rotation;
        glm::mat4 modelMatrix;

        // Axes
        static glm::vec3 RIGHT, UP, FORWARD;
    };
}

#endif //SMARTIN3D_TRANSFORM_H
