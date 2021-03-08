#include "graphics/Texture.h"

smartin::graphics::Texture::Texture(unsigned int _width, unsigned int _height, unsigned int _depth) :
    id(0),
    width(_width),
    height(_height),
    depth(_depth)
{
    type = depth == 4 ? GL_RGBA : GL_RGB;
}

bool smartin::graphics::Texture::Load(unsigned char* imageData) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void smartin::graphics::Texture::Apply(GLuint textureUnit) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}

smartin::graphics::Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void smartin::graphics::DisableTextures() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
