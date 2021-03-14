#include "graphics/lighting/ShadowMap.h"

smartin::graphics::lighting::ShadowMap::ShadowMap(unsigned int _width, unsigned int _height) :
    width(_width),
    height(_height),
    fbo(0),
    shadowMap(0) { }

void smartin::graphics::lighting::ShadowMap::Init() {
    glGenFramebuffers(1, &fbo);
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        throw utils::error::OpenGLException("Framebuffer error: " + std::to_string(status));

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void smartin::graphics::lighting::ShadowMap::Write() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void smartin::graphics::lighting::ShadowMap::Read(GLuint textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}

smartin::graphics::lighting::ShadowMap::~ShadowMap() {
    if (fbo != 0)
        glDeleteFramebuffers(1, &fbo);

    if (shadowMap != 0)
        glDeleteTextures(1, &shadowMap);
}
