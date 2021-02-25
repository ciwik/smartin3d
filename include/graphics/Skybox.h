#ifndef SMARTIN3D_SKYBOX_H
#define SMARTIN3D_SKYBOX_H

#include <array>
#include <string>

#include "graphics/Mesh.h"
#include "graphics/Shader.h"

namespace smartin::graphics {
    class Skybox {
    public:
        Skybox(int width, int height);

        bool Load(const std::array<unsigned char*, 6>& facesImageData, Shader* shader);
        void Apply(GLuint textureUnit, const glm::mat4& view, const glm::mat4& projection);

        ~Skybox();

    private:
        GLuint id;

        Mesh* mesh;
        Shader* shader;

        int width, height;
    };
}

#endif //SMARTIN3D_SKYBOX_H
