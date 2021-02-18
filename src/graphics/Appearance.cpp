#include "graphics/Appearance.h"

smartin::graphics::Appearance::Appearance(smartin::graphics::Mesh* _mesh, smartin::graphics::Material* _material) {
    mesh = _mesh;
    material = _material;
}

void smartin::graphics::Appearance::Render() {
    for (smartin::graphics::Appearance* child : children)
        child->Render();

    if (material != nullptr)
        material->Apply();
    if (mesh != nullptr)
        mesh->Render();
}

smartin::graphics::Appearance::~Appearance() { }
