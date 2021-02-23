#ifndef SMARTIN3D_APPEARANCE_H
#define SMARTIN3D_APPEARANCE_H

#include <vector>

#include "graphics/Mesh.h"
#include "graphics/Material.h"

namespace smartin::graphics {
    class Appearance {
    public:
        Appearance(Mesh* mesh, Material* material);

        void Render();

        ~Appearance();

        Mesh* mesh = nullptr;
        Material* material = nullptr;
    };
}

#endif //SMARTIN3D_APPEARANCE_H
