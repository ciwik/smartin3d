#include "graphics/Material.h"

const glm::vec4 smartin::graphics::Material::defaultColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

smartin::graphics::Material::Material(std::shared_ptr<smartin::graphics::Shader> _shader, unsigned int _textureUnit) :
    shader(_shader),
    textureUnit(_textureUnit)
{
    if (textureUnit == -1)
        textureUnit = settings::MainTextureUnit;
}

void smartin::graphics::Material::SetTexture(std::shared_ptr<smartin::graphics::Texture> _texture) {
    texture = _texture;
}

void smartin::graphics::Material::SetColor(const glm::vec3& _color) {
    color = _color;
    hasColor = true;
}

void smartin::graphics::Material::Apply() const {
    shader->SetVector3("mainColor", hasColor ? color : defaultColor);

    if (texture != nullptr)
        texture->Apply(textureUnit);
}

smartin::graphics::Material::~Material() { }
