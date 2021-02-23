#ifndef SMARTIN3D_ASSETLOADER_H
#define SMARTIN3D_ASSETLOADER_H

#include <array>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "utils/External.h"
#include "graphics/Appearance.h"

namespace smartin::utils::loaders {
    const std::array<std::string, 3> SUPPORTED_TEXTURE_FORMATS = { "tga", "png", "jpg" };
    const std::string TEXTURE_DIR = "textures";
    const std::string SHADER_DIR = "shaders";
    const std::string MODEL_DIR = "models";

    const std::string VERTEX_SHADER_EXTENSION = "vshader";
    const std::string FRAGMENT_SHADER_EXTENSION = "fshader";

    graphics::Texture* LoadTexture(const std::string& filePath);
    graphics::Shader* LoadShader(const std::string& vertexCodePath, const std::string& fragmentCodePath);
    graphics::Appearance* LoadAppearance(const std::string& modelFilePath, graphics::Shader* shader);
}


#endif //SMARTIN3D_ASSETLOADER_H
