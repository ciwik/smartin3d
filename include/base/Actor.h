#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "graphics/Appearance.h"
#include "Transform.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(Transform* transform = new Transform());

        void SetAppearance(graphics::Appearance* appearance);

        bool IsActive() const { return isActive; }
        void SetActive(bool mode) { isActive = mode; }

        bool IsRenderable() const;

        Transform* GetTransform() const { return transform; }
        graphics::Mesh* GetMesh() const { return appearance->mesh; }
        graphics::Material* GetMaterial() const { return appearance->material; }

        virtual void Update();

        void Render();

        ~Actor();

    protected:
        Transform* transform = nullptr;
        graphics::Appearance* appearance = nullptr;

    private:
        bool isActive;
    };

    std::vector<Actor*> GetAllActors();
}

#endif //SMARTIN3D_ACTOR_H
