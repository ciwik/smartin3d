#include "base/Actor.h"

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    delete transform;
}

void smartin::base::Actor::Render() {
    if (!IsRenderable())
        return;

    appearance->Render();
}

smartin::base::Actor::Actor(smartin::base::Transform* _transform) {
    transform = _transform;
}

void smartin::base::Actor::SetAppearance(smartin::graphics::Appearance* _appearance) {
    appearance = _appearance;
}

bool smartin::base::Actor::IsRenderable() const {
    return appearance != nullptr;
}
