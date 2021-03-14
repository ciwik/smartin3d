#ifndef SMARTIN3D_LIGHT_H
#define SMARTIN3D_LIGHT_H

#include "precompiled.h"

#include "ShadowMap.h"

namespace smartin::graphics::lighting {
    class Light {
    public:
        Light();
        Light(GLuint shadowWidth, GLuint shadowHeight, glm::vec3 color,
              GLfloat ambientIntensity, GLfloat diffuseIntensity);

        ~Light();

    protected:
        glm::vec3 color;
        GLfloat ambientIntensity, diffuseIntensity;

        glm::mat4 lightProjection;

        std::unique_ptr<ShadowMap> shadowMap;
    };
}

#endif //SMARTIN3D_LIGHT_H
