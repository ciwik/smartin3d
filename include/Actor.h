#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(graphics::Mesh* mesh, Transform* transform = new Transform());

        bool IsActive() const { return isActive; }
        void SetActive(bool mode) { isActive = mode; }
        Transform* GetTransform() const { return transform; }

        virtual void Update();

        void Render();

        ~Actor();

    protected:
        Transform* transform;
        graphics::Mesh* mesh;

    private:
        bool isActive;
    };
}

#endif //SMARTIN3D_ACTOR_H
