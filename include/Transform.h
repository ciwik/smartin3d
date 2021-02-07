#ifndef SMARTIN3D_TRANSFORM_H
#define SMARTIN3D_TRANSFORM_H

#include <math.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace smartin::base {
    class Transform final {
        // TODO: friend class ...

    public:
        Transform(glm::vec3 position,
                  glm::vec3 size,
                  glm::vec3 eulerAngles);

        Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
                  glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

        glm::vec3 GetPosition() const { return position; }
        glm::vec3 GetSize() const { return size; }
        glm::quat GetRotation() const { return rotation; }
        glm::vec3 GetEulerAngles() const;

        glm::mat4 GetModelMatrix() const { return modelMatrix; }

        glm::vec3 GetRight() const { return glm::normalize(rotation * RIGHT); }
        glm::vec3 GetUp() const { return glm::normalize(rotation * UP); }
        glm::vec3 GetForward() const { return glm::normalize(rotation * FORWARD); }

        void Update();

        void Move(glm::vec3 direction);

        void Scale(glm::vec3 scale);
        void Scale(GLfloat scale);

        void Rotate(glm::quat additionalRotation);
        void Rotate(glm::vec3 eulerAngles);
        void RotateAround(glm::vec3 axis, GLfloat angle);
        void SetRotation(glm::vec3 eulerAngles);

        ~Transform();

    private:
        glm::vec3 position, size;
        glm::quat rotation;

        glm::mat4 modelMatrix;

        // Axes
        static glm::vec3 RIGHT, UP, FORWARD;
    };
}

#endif //SMARTIN3D_TRANSFORM_H
