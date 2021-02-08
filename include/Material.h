#ifndef SMARTIN3D_MATERIAL_H
#define SMARTIN3D_MATERIAL_H

#include <map>
#include <vector>

#include "Shader.h"

namespace smartin::graphics {
    class Material {
    public:
        Material(Shader* shader);
    };

    std::vector<Material*> GetMaterialsByShader(Shader* shader);
}

#endif //SMARTIN3D_MATERIAL_H