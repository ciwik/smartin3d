#include "utils/AssetLoader.h"

std::string BuildPath(const std::string& directory, const std::string& file) {
    return smartin::utils::loaders::ASSETS_ROOT_DIR + directory + file;
}

std::shared_ptr<smartin::graphics::Texture> smartin::utils::loaders::LoadTexture(const std::string& fileName) {
    std::shared_ptr<smartin::graphics::Texture> texture = nullptr;

    std::string filePath = BuildPath(TEXTURES_DIR, fileName);
    int width, height, depth;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &depth, 0);
    if (data != nullptr) {
        texture = std::make_shared<smartin::graphics::Texture>(width, height, depth);
        texture->Load(data);
        stbi_image_free(data);
    }

    return texture;
}

std::shared_ptr<smartin::graphics::Skybox> smartin::utils::loaders::LoadSkybox(const std::array<std::string, 6>& faceTexturePaths, std::shared_ptr<graphics::Shader> shader) {
    std::shared_ptr<smartin::graphics::Skybox> skybox = nullptr;
    std::array<unsigned char*, 6> imagesData;

    int width, height, bitDepth;
    for (size_t i = 0; i < faceTexturePaths.size(); i++) {
        std::string filePath = BuildPath(SKYBOXES_DIR, faceTexturePaths[i]);
        imagesData[i] = stbi_load(filePath.c_str(), &width, &height, &bitDepth, 0);
        if (imagesData[i] == nullptr)
            throw error::AssetException("Couldn't find file at path: " + filePath);
    }

    skybox = std::make_shared<graphics::Skybox>(width, height);
    skybox->Load(imagesData, shader);

    for (size_t i = 0; i < imagesData.size(); i++)
        stbi_image_free(imagesData[i]);

    return skybox;
}

std::shared_ptr<smartin::graphics::Shader> smartin::utils::loaders::LoadShader(const std::string& vertexCodeName, const std::string& fragmentCodeName) {
    std::string vertexCodePath = BuildPath(SHADERS_DIR, vertexCodeName);
    std::string fragmentCodePath = BuildPath(SHADERS_DIR, fragmentCodeName);

    std::string vertexCode = smartin::utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = smartin::utils::io::ReadFile(fragmentCodePath);

    auto shader = std::make_shared<smartin::graphics::Shader>(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

void smartin::utils::loaders::LoadAppearanceForActor(std::shared_ptr<base::Actor> actor, const std::string& modelFileName) {
    std::string modelFilePath = BuildPath(MODELS_DIR, modelFileName);

    auto loader = std::make_unique<ModelLoader>(modelFilePath);
    loader->Load();
    loader->ApplyToActor(actor);
}
