#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "graphics/Appearance.h"
#include "Transform.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(Transform* transform = new Transform());

        void SetAppearance(graphics::Appearance* appearance);

        inline bool IsActive() const { return isActive; }
        inline void SetActive(bool mode) { isActive = mode; }

        bool IsRenderable() const;

        inline Transform* GetTransform() const { return transform; }
        inline graphics::Mesh* GetMesh() const { return appearance->mesh; }
        inline graphics::Material* GetMaterial() const { return appearance->material; }

        virtual void Update();

        void Render();

        ~Actor();

    protected:
        Transform* transform = nullptr;
        graphics::Appearance* appearance = nullptr;

    private:
        bool isActive;
    };
}

#endif //SMARTIN3D_ACTOR_H
