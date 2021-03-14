#include "graphics/lighting/DirectionalLight.h"

smartin::graphics::lighting::DirectionalLight::DirectionalLight() :
    direction(0.0f, -1.0f, 0.0f) { }

smartin::graphics::lighting::DirectionalLight::DirectionalLight(GLuint shadowWidth, GLuint shadowHeight,
                                                                glm::vec3 color, glm::vec3 _direction,
                                                                GLfloat ambientIntensity, GLfloat diffuseIntensity) :
    Light(shadowWidth, shadowHeight, color, ambientIntensity, diffuseIntensity),
    direction(_direction) {

    lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

static const std::string ambientColorKey = "directionalLight.base.color";
static const std::string ambientIntensityKey = "directionalLight.base.ambientIntensity";
static const std::string diffuseIntensityKey = "directionalLight.base.diffuseIntensity";
static const std::string directionKey = "directionalLight.direction";

void smartin::graphics::lighting::DirectionalLight::ApplyTo(std::shared_ptr<Shader> shader) {
    shader->SetVector3(ambientColorKey, color);
    shader->SetFloat(ambientIntensityKey, ambientIntensity);
    shader->SetFloat(diffuseIntensityKey, diffuseIntensity);
    shader->SetVector3(directionKey, direction);
}

glm::mat4 smartin::graphics::lighting::DirectionalLight::CalculateLightTransform() {
    return lightProjection * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

smartin::graphics::lighting::DirectionalLight::~DirectionalLight() { }
