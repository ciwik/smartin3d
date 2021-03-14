#ifndef SMARTIN3D_DIRECTIONALLIGHT_H
#define SMARTIN3D_DIRECTIONALLIGHT_H

#include "Light.h"

namespace smartin::graphics::lighting {
    class DirectionalLight : public Light {
    public:
        DirectionalLight();
        DirectionalLight(GLuint shadowWidth, GLuint shadowHeight,
                         glm::vec3 color, glm::vec3 direction,
                         GLfloat ambientIntensity, GLfloat diffuseIntensity);

        void ApplyTo(std::shared_ptr<Shader> shader) override;

        glm::mat4 CalculateLightTransform();

        ~DirectionalLight();

    private:
        glm::vec3 direction;
    };
}

#endif //SMARTIN3D_DIRECTIONALLIGHT_H
