#include "base/Actor.h"

std::vector<smartin::base::Actor*> actors;

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    delete transform;
}

smartin::base::Actor::Actor(smartin::base::Transform* _transform) {
    transform = _transform;
    actors.push_back(this);
}

bool smartin::base::Actor::IsRenderable() const {
    return !materials.empty();
}

void smartin::base::Actor::SetAppearence(std::map<graphics::Mesh*, graphics::Material*> _materials) {
    materials = _materials;
}

void smartin::base::Actor::Render(glm::mat4 projection, glm::mat4 view) {
    if (!IsRenderable())
        return;

    for (std::pair<graphics::Mesh*, graphics::Material*> p : materials) {
        p.second->Apply(projection, view, transform->GetModelMatrix());
        p.first->Render();
    }
}

std::vector<smartin::base::Actor*> smartin::base::GetAllActors() {
    return actors;
}
