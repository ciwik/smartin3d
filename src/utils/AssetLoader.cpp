#include "utils/AssetLoader.h"

smartin::graphics::Texture* smartin::utils::loaders::LoadTexture(const std::string& fileName) {
    smartin::graphics::Texture* texture = nullptr;

    std::string filePath = TEXTURE_DIR + "/" + fileName;
    int width, height, depth;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &depth, 0);
    if (data != nullptr) {
        texture = new smartin::graphics::Texture(width, height, depth);
        texture->Load(data);
        stbi_image_free(data);
    }

    return texture;
}

smartin::graphics::Shader* smartin::utils::loaders::LoadShader(const std::string& vertexCodeName, const std::string& fragmentCodeName) {
    std::string vertexCodePath = SHADER_DIR + "/" + vertexCodeName;
    std::string fragmentCodePath = SHADER_DIR + "/" + fragmentCodeName;

    std::string vertexCode = smartin::utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = smartin::utils::io::ReadFile(fragmentCodePath);

    smartin::graphics::Shader* shader = new smartin::graphics::Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

void smartin::utils::loaders::LoadAppearanceForActor(base::Actor* actor, const std::string& modelFileName, smartin::graphics::Shader* shader) {
    std::string modelFilePath = MODEL_DIR + "/" + modelFileName;

    ModelLoader* loader = new ModelLoader(modelFilePath);
    loader->Load();

    std::vector<graphics::Appearance*> appearances;
    loader->ConvertToAppearances(appearances);
    delete loader;

    for (graphics::Appearance* appearance : appearances)
        actor->AddAppearance(appearance);
}
