#include "Actor.h"

smartin::base::Actor::Actor(smartin::graphics::Mesh* _mesh, graphics::Shader* _shader, smartin::base::Transform* _transform) {
    mesh = _mesh;
    shader = _shader;
    transform = _transform;
}

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    delete transform;
}

void smartin::base::Actor::Render() {
    if (shader == nullptr || mesh == nullptr)
        return;

    glm::mat4 modelMatrix = transform->GetModelMatrix();
    shader->SetMatrix("model", modelMatrix);

    shader->Validate();
    shader->Apply();

    mesh->Render();
}
