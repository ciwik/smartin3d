#ifndef SMARTIN3D_LIGHT_H
#define SMARTIN3D_LIGHT_H

#include "precompiled.h"

#include "ShadowMap.h"
#include "graphics/Shader.h"

namespace smartin::graphics::lighting {
    class Light {
    public:
        Light();
        Light(GLuint shadowWidth, GLuint shadowHeight, glm::vec3 color,
              GLfloat ambientIntensity, GLfloat diffuseIntensity);

        virtual void ApplyTo(std::shared_ptr<Shader> shader) = 0;

        ~Light();

        std::unique_ptr<ShadowMap> shadowMap;

    protected:
        glm::vec3 color;
        GLfloat ambientIntensity, diffuseIntensity;

        glm::mat4 lightProjection;
    };
}

#endif //SMARTIN3D_LIGHT_H
