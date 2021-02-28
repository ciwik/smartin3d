#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "graphics/Appearance.h"
#include "Transform.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(std::shared_ptr<Transform> transform = std::make_shared<Transform>());

        inline bool IsActive() const { return isActive; }
        inline void SetActive(bool mode) { isActive = mode; }
        inline std::shared_ptr<Transform> GetTransform() const { return transform; }
        virtual void Update();

        void AddAppearance(std::unique_ptr<graphics::Mesh> mesh, std::shared_ptr<graphics::Material> material);
        bool IsRenderable() const;
        void Render();

        ~Actor();

    protected:
        std::shared_ptr<Transform> transform = nullptr;
        std::vector<std::unique_ptr<graphics::Appearance>> appearances;

    private:
        bool isActive;
    };
}

#endif //SMARTIN3D_ACTOR_H
