#include "base/Actor.h"

std::vector<smartin::base::Actor*> actors;

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    delete transform;
}

void smartin::base::Actor::Render() {
    if (material == nullptr || mesh == nullptr)
        return;

    material->Apply();
    mesh->Render();
}

smartin::base::Actor::Actor(smartin::base::Transform* _transform) {
    transform = _transform;
    actors.push_back(this);
}

void smartin::base::Actor::SetAppearence(smartin::graphics::Mesh* _mesh, smartin::graphics::Material* _material) {
    mesh = _mesh;
    material = _material;
}

bool smartin::base::Actor::IsRenderable() const {
    return mesh != nullptr && material != nullptr;
}

std::vector<smartin::base::Actor*> smartin::base::GetAllActors() {
    return actors;
}
