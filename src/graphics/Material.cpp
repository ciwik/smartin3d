#include "graphics/Material.h"

smartin::graphics::Material::Material(smartin::graphics::Shader* _shader) {
    shader = _shader;
}

void smartin::graphics::Material::SetTexture(smartin::graphics::Texture* _texture) {
    texture = _texture;
}

void smartin::graphics::Material::SetColor(glm::vec3 _color) {
    color = _color;
    hasColor = true;
}

smartin::graphics::Material::~Material() {
    delete texture;
}

void smartin::graphics::Material::Apply(glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
    shader->Validate();
    shader->Apply();

    shader->SetMatrix("projection", projection);
    shader->SetMatrix("view", view);
    shader->SetMatrix("model", model);

    if (hasColor)
        shader->SetVector3("mainColor", color);

    if (texture != nullptr) {
        texture->Apply();
        shader->SetTexture("mainTex", texture);
    }
}
