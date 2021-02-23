#ifndef SMARTIN3D_ASSETLOADER_H
#define SMARTIN3D_ASSETLOADER_H

#include <array>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "base/Actor.h"
#include "utils/External.h"
#include "utils/ModelLoader.h"
#include "graphics/Appearance.h"

namespace smartin::utils::loaders {
    const std::array<std::string, 3> SUPPORTED_TEXTURE_FORMATS = { "tga", "png", "jpg" };
    const std::string TEXTURE_DIR = "textures";
    const std::string SHADER_DIR = "shaders";
    const std::string MODEL_DIR = "models";

    graphics::Texture* LoadTexture(const std::string& fileName);
    graphics::Shader* LoadShader(const std::string& vertexCodeName, const std::string& fragmentCodeName);
    void LoadAppearanceForActor(base::Actor* actor, const std::string& modelFileName, graphics::Shader* shader);
}

#endif //SMARTIN3D_ASSETLOADER_H
