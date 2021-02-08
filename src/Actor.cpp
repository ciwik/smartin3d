#include "Actor.h"

std::map<smartin::graphics::Material*, std::vector<smartin::base::Actor*>> actorsByUsedMaterial;

smartin::base::Actor::Actor(smartin::graphics::Mesh* _mesh, smartin::graphics::Material* material, smartin::base::Transform* _transform) {
    mesh = _mesh;
    transform = _transform;

    if (material != nullptr)
        actorsByUsedMaterial[material].push_back(this);
}

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    delete transform;
}

void smartin::base::Actor::Render() {
    if (mesh == nullptr)
        return;

    mesh->Render();
}

std::vector<smartin::base::Actor*> smartin::base::GetActorsUsingMaterial(smartin::graphics::Material* material) {
    return actorsByUsedMaterial[material];
}
