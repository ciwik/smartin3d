#ifndef SMARTIN3D_APPEARANCE_H
#define SMARTIN3D_APPEARANCE_H

#include <vector>

#include "graphics/Mesh.h"
#include "graphics/Material.h"

namespace smartin::graphics {
    class Appearance {
    public:
        Appearance(std::unique_ptr<Mesh> mesh, std::shared_ptr<Material> material);

        void Render();

        ~Appearance();

        std::unique_ptr<Mesh> mesh = nullptr;
        std::shared_ptr<Material> material = nullptr;
    };
}

#endif //SMARTIN3D_APPEARANCE_H
