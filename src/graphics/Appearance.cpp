#include "graphics/Appearance.h"

smartin::graphics::Appearance::Appearance(smartin::graphics::Mesh* _mesh, smartin::graphics::Material* _material) {
    mesh = _mesh;
    material = _material;
}

void smartin::graphics::Appearance::Render() {
    for (smartin::graphics::Appearance* child : children)
        child->Render();

    material->Apply();
    mesh->Render();
}

smartin::graphics::Appearance::~Appearance() { }
