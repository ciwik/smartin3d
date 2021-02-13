#ifndef SMARTIN3D_ACTOR_H
#define SMARTIN3D_ACTOR_H

#include "graphics/Mesh.h"
#include "Transform.h"
#include "graphics/Material.h"

namespace smartin::base {
    class Actor {
    public:
        Actor(Transform* transform = new Transform());

        void SetAppearence(std::map<graphics::Mesh*, graphics::Material*> materials);

        bool IsActive() const { return isActive; }
        void SetActive(bool mode) { isActive = mode; }

        bool IsRenderable() const;

        Transform* GetTransform() const { return transform; }

        virtual void Update();

        void Render(glm::mat4 projection, glm::mat4 view);

        ~Actor();

    protected:
        std::map<graphics::Mesh*, graphics::Material*> materials;
        Transform* transform = nullptr;

    private:
        bool isActive;
    };

    std::vector<Actor*> GetAllActors();
}

#endif //SMARTIN3D_ACTOR_H
