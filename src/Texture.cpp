#include "Texture.h"

smartin::graphics::Texture::Texture(std::string _filePath, bool withAlpha) {
    filePath = _filePath;
    type = withAlpha ? GL_RGBA : GL_RGB;

    id = 0;
    width = 0;
    height = 0;
    depth = 0;
}

bool smartin::graphics::Texture::Load() {
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &depth, 0);
    if (data == nullptr) {
        utils::log::E("Texture", "Failed to find: " + filePath);
        return false;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return true;
}

void smartin::graphics::Texture::Apply() {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, id);
}

smartin::graphics::Texture::~Texture() {
    glDeleteTextures(1, &id);
    id = 0;
    width = 0;
    height = 0;
    depth = 0;
    filePath = nullptr;
}
