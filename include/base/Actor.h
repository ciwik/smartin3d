#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "graphics/Mesh.h"
#include "Transform.h"
#include "graphics/Material.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(Transform* transform = new Transform());

        void SetAppearence(graphics::Mesh* mesh, graphics::Material* material);

        bool IsActive() const { return isActive; }
        void SetActive(bool mode) { isActive = mode; }

        bool IsRenderable() const;

        Transform* GetTransform() const { return transform; }
        graphics::Mesh* GetMesh() const { return mesh; }
        graphics::Material* GetMaterial() const { return material; }

        virtual void Update();

        void Render();

        ~Actor();

    protected:
        Transform* transform = nullptr;
        graphics::Mesh* mesh = nullptr;
        graphics::Material* material = nullptr;

    private:
        bool isActive;
    };

    std::vector<Actor*> GetAllActors();
}

#endif //SMARTIN3D_ACTOR_H
