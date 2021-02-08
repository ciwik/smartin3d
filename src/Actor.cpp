#include "Actor.h"

smartin::base::Actor::Actor(smartin::graphics::Mesh* _mesh, smartin::base::Transform* _transform) {
    mesh = _mesh;
    transform = _transform;
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

    glm::mat4 modelMatrix = transform->GetModelMatrix();

    mesh->Render();
}
