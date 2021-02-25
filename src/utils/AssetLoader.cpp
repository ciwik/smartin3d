#include "utils/AssetLoader.h"

std::string BuildPath(const std::string& directory, const std::string& file) {
    return smartin::utils::loaders::ASSETS_ROOT_DIR + directory + file;
}

smartin::graphics::Texture* smartin::utils::loaders::LoadTexture(const std::string& fileName) {
    smartin::graphics::Texture* texture = nullptr;

    std::string filePath = BuildPath(TEXTURES_DIR, fileName);
    int width, height, depth;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &depth, 0);
    if (data != nullptr) {
        texture = new smartin::graphics::Texture(width, height, depth);
        texture->Load(data);
        stbi_image_free(data);
    }

    return texture;
}

smartin::graphics::Skybox* smartin::utils::loaders::LoadSkybox(const std::array<std::string, 6>& faceTexturePaths, graphics::Shader* shader) {
    smartin::graphics::Skybox* skybox = nullptr;
    std::array<unsigned char*, 6> imagesData;

    int width, height, bitDepth;
    for (size_t i = 0; i < faceTexturePaths.size(); i++) {
        std::string filePath = BuildPath(SKYBOXES_DIR, faceTexturePaths[i]);
        imagesData[i] = stbi_load(filePath.c_str(), &width, &height, &bitDepth, 0);
        if (imagesData[i] == nullptr) {
            utils::log::E("AssetLoader", "Couldn't find file at path: " + filePath);
            return nullptr;
        }
    }

    skybox = new graphics::Skybox(width, height);
    skybox->Load(imagesData, shader);

    for (size_t i = 0; i < imagesData.size(); i++)
        stbi_image_free(imagesData[i]);

    return skybox;
}

smartin::graphics::Shader* smartin::utils::loaders::LoadShader(const std::string& vertexCodeName, const std::string& fragmentCodeName) {
    std::string vertexCodePath = BuildPath(SHADERS_DIR, vertexCodeName);
    std::string fragmentCodePath = BuildPath(SHADERS_DIR, fragmentCodeName);

    std::string vertexCode = smartin::utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = smartin::utils::io::ReadFile(fragmentCodePath);

    smartin::graphics::Shader* shader = new smartin::graphics::Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

void smartin::utils::loaders::LoadAppearanceForActor(base::Actor* actor, const std::string& modelFileName, smartin::graphics::Shader* shader) {
    std::string modelFilePath = BuildPath(MODELS_DIR, modelFileName);

    ModelLoader* loader = new ModelLoader(modelFilePath);
    loader->Load();

    std::vector<graphics::Appearance*> appearances;
    loader->ConvertToAppearances(appearances);
    delete loader;

    for (graphics::Appearance* appearance : appearances)
        actor->AddAppearance(appearance);
}
