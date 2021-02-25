#include "utils/AssetUtils.h"

// Actors
smartin::base::Actor* smartin::utils::FindActor(const std::string& name) {
    return holders::actors.Get(name);
}

smartin::base::Actor* smartin::utils::CreateActor(const std::string& name, const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles) {
    base::Transform* transform = new base::Transform(position, size, eulerAngles);
    smartin::base::Actor* actor = new smartin::base::Actor(transform);
    holders::actors.Add(name, actor);

    return actor;
}

smartin::base::Actor* smartin::utils::CreateActorWithAppearance(const std::string& name, const std::string& modelFileName, const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles) {
    smartin::base::Actor* actor = CreateActor(name, position, size, eulerAngles);
    if (actor != nullptr)
        loaders::LoadAppearanceForActor(actor, modelFileName, GetShader(DEFAULT_SHADER_NAME));  // TODO

    return actor;
}

std::vector<smartin::base::Actor*> smartin::utils::GetAllActors() {
    return holders::actors.GetAll();
}

smartin::base::Camera* smartin::utils::CreateCamera(float fov, float aspect, const glm::vec3& position, const glm::vec3& eulerAngles) {
    base::Transform* transform = new base::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), eulerAngles);
    base::Camera* camera = new base::Camera(transform);
    camera->fieldOfView = fov;
    camera->aspect = aspect;

    holders::actors.Add(DEFAULT_CAMERA_NAME, camera);

    return camera;
}

void smartin::utils::DestroyActor(const std::string& name) {
    holders::actors.Remove(name);
}

// Assets
smartin::graphics::Shader* smartin::utils::GetShader(const std::string& name) {
    return holders::shaders.Get(name);
}

smartin::graphics::Shader* smartin::utils::CreateShader(const std::string& name) {
    graphics::Shader* shader = nullptr;

    std::string vertexShaderPath = name + "." + VERTEX_SHADER_EXTENSION;
    std::string fragmentShaderPath = name + "." + FRAGMENT_SHADER_EXTENSION;
    shader = loaders::LoadShader(vertexShaderPath, fragmentShaderPath);

    if (shader != nullptr && shader->Compile() && shader->Validate()) {
        holders::shaders.Add(name, shader);
    } else {
        delete shader;
        shader = nullptr;
    }

    return shader;
}

void smartin::utils::DestroyShader(const std::string& name) {
    holders::shaders.Remove(name);
}

smartin::graphics::Texture* smartin::utils::GetTexture(const std::string& name) {
    return holders::textures.Get(name);
}

smartin::graphics::Texture* smartin::utils::CreateTexture(const std::string& name, const std::string& fileName) {
    graphics::Texture* texture = loaders::LoadTexture(fileName);

    if (texture != nullptr)
        holders::textures.Add(name, texture);

    return texture;
}

void smartin::utils::DestroyTexture(const std::string& name) {
    holders::textures.Remove(name);
}

smartin::graphics::Material* smartin::utils::GetMaterial(const std::string& name) {
    return holders::materials.Get(name);
}

smartin::graphics::Material* smartin::utils::CreateMaterial(const std::string& name, const std::string& textureName, const glm::vec3& color, const std::string& shaderName) {
    graphics::Material* material = nullptr;

    graphics::Shader* shader = GetShader(shaderName);
    if (shader != nullptr) {
        material = new graphics::Material(shader);
        material->SetColor(color);

        graphics::Texture* texture = GetTexture(textureName);
        if (texture != nullptr)
            material->SetTexture(texture);
    }

    if (material != nullptr)
        holders::materials.Add(name, material);

    return material;
}

smartin::graphics::Material* smartin::utils::CreateMaterial(const std::string& name, smartin::graphics::Texture* texture) {
    graphics::Material* material = nullptr;

    if (texture != nullptr) {
        graphics::Shader* shader = GetShader();
        if (shader != nullptr) {
            material = new graphics::Material(shader);
            material->SetTexture(texture);
        }
    }

    if (material != nullptr)
        holders::materials.Add(name, material);

    return material;
}

void smartin::utils::DestroyMaterial(const std::string& name) {
    holders::materials.Remove(name);
}

smartin::graphics::Skybox* smartin::utils::GetSkybox() {
    return holders::skybox;
}

smartin::graphics::Skybox* smartin::utils::CreateSkybox(const std::array<std::string, 6>& faceTexturePaths) {
    graphics::Shader* shader = utils::GetShader(DEFAULT_SKY_SHADER_NAME);
    if (shader == nullptr)
        shader = utils::CreateShader(DEFAULT_SKY_SHADER_NAME);

    holders::skybox = loaders::LoadSkybox(faceTexturePaths, shader);
    return holders::skybox;
}

void smartin::utils::DestroySkybox() {
    delete holders::skybox;
    DestroyShader(DEFAULT_SKY_SHADER_NAME);
}
