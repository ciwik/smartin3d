#include "utils/AssetUtils.h"

const std::string TEXTURE_DIR = "textures";
const std::array<std::string, 3> SUPPORTED_TEXTURE_FORMATS = { "tga", "png", "jpg" };

const std::string SHADER_DIR = "shaders";
const std::string VERTEX_SHADER_EXTENSION = "vshader";
const std::string FRAGMENT_SHADER_EXTENSION = "fshader";

namespace loaders {
    smartin::graphics::Texture* LoadTexture(std::string filePath);
    smartin::graphics::Shader* LoadShader(std::string vertexCodePath, std::string fragmentCodePath);
}

namespace holders {
    std::map<std::string, smartin::graphics::Texture*> textures;
    smartin::graphics::Texture* GetTexture(std::string name) { return textures[name]; }

    std::map<std::string, smartin::graphics::Shader*> shaders;
    smartin::graphics::Shader* GetShader(std::string name) { return shaders[name]; }
}

std::string GetNameByPath(std::string const &path);

smartin::graphics::Shader* smartin::utils::GetOrCreateShader(std::string name) {
    smartin::graphics::Shader* result = nullptr;

    result = holders::GetShader(name);
    if (result == nullptr) {
        std::string vertexShaderPath = SHADER_DIR + "/" + name + "." + VERTEX_SHADER_EXTENSION;
        std::string fragmentShaderPath = SHADER_DIR + "/" + name + "." + FRAGMENT_SHADER_EXTENSION;

        result = loaders::LoadShader(vertexShaderPath, fragmentShaderPath);
        if (result != nullptr) {
            if (result->Compile() && result->Validate()) {
                holders::shaders[name] = result;
            } else {
                delete result;
                result = nullptr;
            }
        }
    }

    if (result == nullptr)
        utils::log::E("AssetUtils", "Failed to find shader: " + name);

    return result;
}

smartin::graphics::Texture* smartin::utils::GetOrCreateTexture(std::string name) {
    smartin::graphics::Texture* result = nullptr;

    std::string _name = GetNameByPath(name);
    result = holders::GetTexture(_name);
    if (result == nullptr) {
        std::string path = TEXTURE_DIR + "/" + name;

        result = loaders::LoadTexture(path);
        if (result == nullptr) {
            // Try to add all possible extensions
            for (std::string ext : SUPPORTED_TEXTURE_FORMATS) {
                std::string _path = path + "." + ext;
                result = loaders::LoadTexture(_path);
                if (result != nullptr)
                    break;
            }

            if (result != nullptr)
                holders::textures[_name] = result;
        }
    }

    if (result == nullptr)
        utils::log::E("AssetUtils", "Failed to find texture: " + name);

    return result;
}

smartin::graphics::Material* smartin::utils::GetOrCreateMaterial(std::string textureName, std::string shaderName) {
    return nullptr;
}

// Loaders
smartin::graphics::Texture* loaders::LoadTexture(std::string filePath) {
    smartin::graphics::Texture* texture = nullptr;

    int width, height, depth;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &depth, 0);
    if (data != nullptr) {
        texture = new smartin::graphics::Texture(width, height, depth);
        texture->Load(data);
        stbi_image_free(data);
    }

    return texture;
}

smartin::graphics::Shader* loaders::LoadShader(std::string vertexCodePath, std::string fragmentCodePath) {
    std::string vertexCode = smartin::utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = smartin::utils::io::ReadFile(fragmentCodePath);

    smartin::graphics::Shader* shader = new smartin::graphics::Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

std::string GetNameByPath(std::string const &path) {
    int dotPosition = path.length() - 1;
    for (int i = path.length() - 1; i >= 0; i--) {
        if (path[i] == '.') {
            dotPosition = i;
            break;
        }
    }

    return path.substr(0, dotPosition + 1);
}
