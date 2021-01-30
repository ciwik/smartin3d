#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "Transform.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(Transform* transform = new Transform());

        bool IsActive() { return isActive; }
        void SetActive(bool mode) { isActive = mode; }
        Transform* GetTransform() { return transform; }

        virtual void Update();

        ~Actor();

    protected:
        Transform* transform;

    private:
        bool isActive;
    };
}

#endif //SMARTIN3D_ACTOR_H
