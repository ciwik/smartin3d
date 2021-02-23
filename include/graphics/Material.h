#ifndef SMARTIN3D_MATERIAL_H
#define SMARTIN3D_MATERIAL_H

#include <map>
#include <vector>

#include "graphics/Settings.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace smartin::graphics {
    class Material {
    public:
        Material(Shader* shader, unsigned int textureUnit = -1);

        inline Shader* GetShader() const { return shader; }

        void SetTexture(Texture* texture);
        void SetColor(const glm::vec3& color);

        void Apply();

        ~Material();

    private:
        Texture* texture = nullptr;
        glm::vec3 color; bool hasColor;
        unsigned int textureUnit;

        Shader* shader;
    };
}

#endif //SMARTIN3D_MATERIAL_H