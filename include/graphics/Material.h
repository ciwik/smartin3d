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
        Material(std::shared_ptr<Shader> shader, unsigned int textureUnit = -1);

        inline std::shared_ptr<Shader> GetShader() const { return shader; }
        inline std::shared_ptr<Texture> GetTexture() const { return texture; }

        void SetTexture(std::shared_ptr<Texture> texture);
        void SetColor(const glm::vec3& color);

        void Apply();

        ~Material();

    private:
        std::shared_ptr<Texture> texture = nullptr;
        glm::vec3 color; bool hasColor = false;
        unsigned int textureUnit;
        std::shared_ptr<Shader> shader;

        const glm::vec4 defaultColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    };
}

#endif //SMARTIN3D_MATERIAL_H