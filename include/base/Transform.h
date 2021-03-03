#ifndef SMARTIN3D_TRANSFORM_H
#define SMARTIN3D_TRANSFORM_H

#include "precompiled.h"

namespace smartin::base {
    class Transform final {
    public:
        Transform(const glm::vec3& position,
                  const glm::vec3& size,
                  const glm::vec3& eulerAngles);

        Transform(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                  const glm::vec3& size = glm::vec3(1.0f, 1.0f, 1.0f),
                  const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

        inline glm::vec3 GetPosition() const { return position; }
        inline glm::vec3 GetSize() const { return size; }
        inline glm::quat GetRotation() const { return rotation; }
        glm::vec3 GetEulerAngles() const;

        inline glm::mat4 GetModelMatrix() const { return modelMatrix; }

        inline glm::vec3 GetRight() const { return glm::normalize(rotation * RIGHT); }
        inline glm::vec3 GetUp() const { return glm::normalize(rotation * UP); }
        inline glm::vec3 GetForward() const { return glm::normalize(rotation * FORWARD); }

        void Update();

        void Move(const glm::vec3& direction);
        void SetPosition(const glm::vec3& position);

        void Scale(const glm::vec3& scale);
        void Scale(GLfloat scale);

        void Rotate(const glm::quat& additionalRotation);
        void Rotate(const glm::vec3& eulerAngles);
        void RotateAround(const glm::vec3& axis, GLfloat angle);
        void SetRotation(const glm::vec3& eulerAngles);

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
