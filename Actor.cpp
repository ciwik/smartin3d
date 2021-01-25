#include "Actor.h"

smartin::base::Actor::Actor(smartin::base::Transform* _transform) : transform(_transform) { }

void smartin::base::Actor::Update() {
    transform->Update();
}

smartin::base::Actor::~Actor() {
    delete transform;
}
