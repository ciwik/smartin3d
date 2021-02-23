#include "graphics/Material.h"

smartin::graphics::Material::Material(smartin::graphics::Shader* _shader) {
    shader = _shader;
}

void smartin::graphics::Material::SetTexture(smartin::graphics::Texture* _texture) {
    texture = _texture;
}

void smartin::graphics::Material::SetColor(const glm::vec3& _color) {
    color = _color;
    hasColor = true;
}

void smartin::graphics::Material::Apply() {
    shader->Apply();

    if (hasColor)
        shader->SetVector3("mainColor", color);

    if (texture != nullptr) {
        texture->Apply();
        shader->SetTexture("mainTex", texture);
    }
}

smartin::graphics::Material::~Material() {
    delete texture;
}
