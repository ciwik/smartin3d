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

void smartin::base::Actor::AddAppearance(std::unique_ptr<graphics::Appearance> appearance) {
    if (appearance->material != nullptr && appearance->mesh != nullptr)
        appearances.push_back(std::move(appearance));
}

bool smartin::base::Actor::IsRenderable() const {
    return !appearances.empty() && isActive;
}

std::vector<std::shared_ptr<smartin::graphics::Material>> smartin::base::Actor::GetAllUsedMaterials() const {
    std::vector<std::shared_ptr<smartin::graphics::Material>> materials;

    if (isActive) {
        for (const auto &appearance : appearances)
            materials.push_back(appearance->material);
    }

    return materials;
}
