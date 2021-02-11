#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "graphics/Mesh.h"
#include "Transform.h"
#include "graphics/Material.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(graphics::Mesh* mesh, graphics::Material* material, Transform* transform = new Transform());

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

    std::vector<Actor*> GetActorsUsingMaterial(graphics::Material* material);
}

#endif //SMARTIN3D_ACTOR_H
