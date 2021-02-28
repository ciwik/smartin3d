#include "graphics/Appearance.h"

smartin::graphics::Appearance::Appearance(std::unique_ptr<Mesh> _mesh, std::shared_ptr<Material> _material) {
    mesh = std::move(_mesh);
    material = _material;
}

void smartin::graphics::Appearance::Render() {
    material->Apply();
    mesh->Render();
}

smartin::graphics::Appearance::~Appearance() { }
