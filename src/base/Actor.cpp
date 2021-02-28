#include "base/Actor.h"

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    appearances.clear();
}

void smartin::base::Actor::Render() {
    if (!IsRenderable())
        return;

    for (auto& appearance : appearances)
        appearance->Render();
}

smartin::base::Actor::Actor(std::shared_ptr<Transform> _transform) {
    transform = _transform;
}

void smartin::base::Actor::AddAppearance(std::unique_ptr<graphics::Mesh> mesh, std::shared_ptr<graphics::Material> material) {
    if (material != nullptr && mesh != nullptr)
        appearances.push_back(std::make_unique<graphics::Appearance>(std::move(mesh), material));
}

bool smartin::base::Actor::IsRenderable() const {
    return !appearances.empty() && isActive;
}
