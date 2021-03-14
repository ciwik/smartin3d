#ifndef SMARTIN3D_ASSETLOADER_H
#define SMARTIN3D_ASSETLOADER_H

#include "precompiled.h"

#include "base/Actor.h"
#include "utils/Exceptions.h"
#include "utils/ModelLoader.h"
#include "graphics/Appearance.h"
#include "graphics/Skybox.h"

namespace smartin::utils::loaders {
    static const std::string assetsRootDir = "assets/";
    static const std::string texturesDir = "textures/";
    static const std::string skyboxesDir = texturesDir + "skyboxes/";
    static const std::string shadersDir = "shaders/";
    static const std::string modelsDir = "models/";

    std::shared_ptr<graphics::Texture> LoadTexture(const std::string& fileName);
    std::shared_ptr<graphics::Skybox> LoadSkybox(const std::array<std::string, 6>& faceTexturePaths, std::shared_ptr<graphics::Shader> shader);
    std::shared_ptr<graphics::Shader> LoadShader(const std::string& vertexCodeName, const std::string& fragmentCodeName);
    void LoadAppearanceForActor(std::shared_ptr<base::Actor> actor, const std::string& modelFileName);
}

#endif //SMARTIN3D_ASSETLOADER_H
