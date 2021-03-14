#include "graphics/lighting/Light.h"

smartin::graphics::lighting::Light::Light() :
    color(1.0f, 1.0f, 1.0f),
    ambientIntensity(1.0f),
    diffuseIntensity(0.0f) { }

smartin::graphics::lighting::Light::Light(GLuint shadowWidth, GLuint shadowHeight, glm::vec3 _color,
                                          GLfloat _ambientIntensity, GLfloat _diffuseIntensity) :
    color(_color),
    ambientIntensity(_ambientIntensity),
    diffuseIntensity(_diffuseIntensity) {

    shadowMap = std::make_unique<ShadowMap>(shadowWidth, shadowHeight);
    shadowMap->Init();
}

smartin::graphics::lighting::Light::~Light() { }
