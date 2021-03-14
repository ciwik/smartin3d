#ifndef SMARTIN3D_SHADOWMAP_H
#define SMARTIN3D_SHADOWMAP_H

#include "precompiled.h"

#include "utils/Exceptions.h"

namespace smartin::graphics::lighting {
    class ShadowMap {
    public:
        ShadowMap(unsigned int width, unsigned int height);

        virtual void Init();
        virtual void Write();
        virtual void Read(GLuint textureUnit);

        ~ShadowMap();

    protected:
        GLuint fbo, shadowMap;
        unsigned int width, height;
    };
}

#endif //SMARTIN3D_SHADOWMAP_H
