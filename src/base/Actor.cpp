#include "base/Actor.h"

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    delete transform;
    for (smartin::graphics::Appearance* appearance : appearances)
        delete appearance;
}

void smartin::base::Actor::Render() {
    if (!IsRenderable())
        return;

    for (graphics::Appearance* appearance : appearances)
        appearance->Render();
}

smartin::base::Actor::Actor(smartin::base::Transform* _transform) {
    transform = _transform;
}

void smartin::base::Actor::AddAppearance(smartin::graphics::Appearance* appearance) {
    if (appearance->material != nullptr && appearance->mesh != nullptr)
        appearances.push_back(appearance);
}

bool smartin::base::Actor::IsRenderable() const {
    return !appearances.empty();
}

std::vector<smartin::graphics::Material*> smartin::base::Actor::GetAllUsedMaterials() const {
    std::vector<smartin::graphics::Material*> materials;

    for (smartin::graphics::Appearance* appearance : appearances)
        materials.push_back(appearance->material);

    return materials;
}
