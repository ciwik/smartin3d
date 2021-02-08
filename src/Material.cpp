#include "Material.h"

std::map<smartin::graphics::Shader*, std::vector<smartin::graphics::Material*>> materialInstances;

smartin::graphics::Material::Material(smartin::graphics::Shader *shader) {
    materialInstances[shader].push_back(this);
}

std::vector<smartin::graphics::Material*> smartin::graphics::GetMaterialsByShader(smartin::graphics::Shader* shader) {
    return materialInstances[shader];
}