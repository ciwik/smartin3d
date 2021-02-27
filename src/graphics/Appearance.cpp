#include "graphics/Appearance.h"

smartin::graphics::Appearance::Appearance(smartin::graphics::Mesh* _mesh, smartin::graphics::Material* _material) {
    mesh = _mesh;
    material = _material;
}

void smartin::graphics::Appearance::Render() {
    material->Apply();
    mesh->Render();
}

smartin::graphics::Appearance::~Appearance() {
    delete mesh;
}
