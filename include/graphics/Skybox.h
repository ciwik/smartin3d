#ifndef SMARTIN3D_SKYBOX_H
#define SMARTIN3D_SKYBOX_H

#include "precompiled.h"

#include "graphics/Mesh.h"
#include "graphics/Shader.h"

namespace smartin::graphics {
    class Skybox {
    public:
        Skybox(int width, int height);

        bool Load(const std::array<unsigned char*, 6>& facesImageData, std::shared_ptr<Shader> shader);
        void Apply(GLuint textureUnit, const glm::mat4& view, const glm::mat4& projection);

        ~Skybox();

    private:
        GLuint id;

        std::unique_ptr<Mesh> mesh;
        std::shared_ptr<Shader> shader;

        int width, height;
    };
}

#endif //SMARTIN3D_SKYBOX_H
