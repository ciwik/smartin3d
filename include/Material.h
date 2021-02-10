#ifndef SMARTIN3D_MATERIAL_H
#define SMARTIN3D_MATERIAL_H

#include <map>
#include <vector>

#include "Shader.h"
#include "Texture.h"

namespace smartin::graphics {
    class Material {
    public:
        Material(Shader* shader);

        void SetTexture(Texture* texture);
        void SetColor(glm::vec3 color);

        void Apply();

        ~Material();

    private:
        Texture* texture = nullptr;
        glm::vec3 color; bool hasColor;

        Shader* shader;
    };

    std::vector<Material*> GetMaterialsByShader(Shader* shader);
}

#endif //SMARTIN3D_MATERIAL_H