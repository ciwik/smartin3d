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
#include "graphics/Skybox.h"

namespace smartin::utils::loaders {
    const std::string ASSETS_ROOT_DIR = "assets/";
    const std::string TEXTURES_DIR = "textures/";
    const std::string SKYBOXES_DIR = TEXTURES_DIR + "skyboxes/";
    const std::string SHADERS_DIR = "shaders/";
    const std::string MODELS_DIR = "models/";

    graphics::Texture* LoadTexture(const std::string& fileName);
    graphics::Skybox* LoadSkybox(const std::array<std::string, 6>& faceTexturePaths, graphics::Shader* shader);
    graphics::Shader* LoadShader(const std::string& vertexCodeName, const std::string& fragmentCodeName);
    void LoadAppearanceForActor(base::Actor* actor, const std::string& modelFileName, graphics::Shader* shader);
}

#endif //SMARTIN3D_ASSETLOADER_H
