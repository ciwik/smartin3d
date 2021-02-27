#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "graphics/Appearance.h"
#include "Transform.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(Transform* transform = new Transform());

        inline bool IsActive() const { return isActive; }
        inline void SetActive(bool mode) { isActive = mode; }
        inline Transform* GetTransform() const { return transform; }
        virtual void Update();

        void AddAppearance(graphics::Appearance* appearance);
        bool IsRenderable() const;
        std::vector<graphics::Material*> GetAllUsedMaterials() const;
        void Render();

        ~Actor();

    protected:
        Transform* transform = nullptr;
        std::vector<graphics::Appearance*> appearances;

    private:
        bool isActive;
    };
}

#endif //SMARTIN3D_ACTOR_H
