#ifndef SMARTIN3D_TEXTURE_H
#define SMARTIN3D_TEXTURE_H

#include <GL/glew.h>

#include <string>

#include "utils/External.h"
#include "utils/Log.h"

namespace smartin::graphics {
    class Texture {
    public:
        Texture(int width, int height, int depth);

        bool Load(unsigned char* imageData);
        void Apply(GLuint textureUnit);

        ~Texture();

        GLuint id;
    private:
        GLenum type;
        int width, height, depth;
    };
}

#endif //SMARTIN3D_TEXTURE_H
