#include "graphics/Material.h"

smartin::graphics::Material::Material(std::shared_ptr<smartin::graphics::Shader> _shader, unsigned int _textureUnit) {
    shader = _shader;

    if (_textureUnit == -1)
        _textureUnit = settings::MainTextureUnit;
    textureUnit = _textureUnit;
}

void smartin::graphics::Material::SetTexture(std::shared_ptr<smartin::graphics::Texture> _texture) {
    texture = _texture;
}

void smartin::graphics::Material::SetColor(const glm::vec3& _color) {
    color = _color;
    hasColor = true;
}

void smartin::graphics::Material::Apply() {
    if (hasColor)
        shader->SetVector3("mainColor", color);

    if (texture != nullptr)
        texture->Apply(textureUnit);
}

smartin::graphics::Material::~Material() { }
