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

        Shader* GetShader() const { return shader; }

        void SetTexture(Texture* texture);
        void SetColor(glm::vec3 color);

        void Apply(glm::mat4 projection, glm::mat4 view, glm::mat4 model);

        ~Material();

    private:
        Texture* texture = nullptr;
        glm::vec3 color; bool hasColor;

        Shader* shader;
    };
}

#endif //SMARTIN3D_MATERIAL_H