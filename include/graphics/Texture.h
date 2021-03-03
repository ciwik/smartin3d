#ifndef SMARTIN3D_TEXTURE_H
#define SMARTIN3D_TEXTURE_H

#include "precompiled.h"

#include "utils/Log.h"

namespace smartin::graphics {
    class Texture final {
    public:
        Texture(int width, int height, int depth);

        bool Load(unsigned char* imageData);
        void Apply(GLuint textureUnit);

        ~Texture();

    private:
        GLuint id;
        GLenum type;
        int width, height, depth;
    };

    void DisableTextures();
}

#endif //SMARTIN3D_TEXTURE_H
