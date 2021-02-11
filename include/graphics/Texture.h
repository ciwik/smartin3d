#ifndef SMARTIN3D_TEXTURE_H
#define SMARTIN3D_TEXTURE_H

#include <GL/glew.h>

#include <string>

#include "utils/External.h"
#include "utils/Log.h"

namespace smartin::graphics {
    class Texture {
    public:
        Texture(std::string filePath, bool withAlpha = false);

        bool Load();
        void Apply();

        ~Texture();

        GLuint id;
    private:
        GLenum type;
        int width, height, depth;

        std::string filePath;
    };
}

#endif //SMARTIN3D_TEXTURE_H
