#include "Material.h"

std::map<smartin::graphics::Shader*, std::vector<smartin::graphics::Material*>> materialInstances;

smartin::graphics::Material::Material(smartin::graphics::Shader* _shader) {
    shader = _shader;
    materialInstances[shader].push_back(this);
}

void smartin::graphics::Material::SetTexture(smartin::graphics::Texture* _texture) {
    texture = _texture;
}

void smartin::graphics::Material::SetColor(glm::vec3 _color) {
    color = _color;
    hasColor = true;
}

void smartin::graphics::Material::Apply() {
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

std::vector<smartin::graphics::Material*> smartin::graphics::GetMaterialsByShader(smartin::graphics::Shader* shader) {
    return materialInstances[shader];
}