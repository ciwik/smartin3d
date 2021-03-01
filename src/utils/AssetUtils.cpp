#include "utils/AssetUtils.h"

// Actors
std::shared_ptr<smartin::base::Actor> smartin::utils::FindActor(const std::string& name) {
    return holders::actors.Get(name);
}

std::shared_ptr<smartin::base::Actor> smartin::utils::CreateActor(const std::string& name, const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles) {
    auto transform = std::make_shared<base::Transform>(position, size, eulerAngles);
    auto actor = std::make_shared<base::Actor>(transform);
    holders::actors.Add(name, actor);

    return actor;
}

std::shared_ptr<smartin::base::Actor> smartin::utils::CreateActorWithAppearance(const std::string& name, const std::string& modelFileName, const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles) {
    auto actor = CreateActor(name, position, size, eulerAngles);
    if (actor != nullptr)
        loaders::LoadAppearanceForActor(actor, modelFileName);  // TODO

    return actor;
}

std::vector<std::shared_ptr<smartin::base::Actor>> smartin::utils::GetAllActors() {
    return holders::actors.GetAll();
}

std::shared_ptr<smartin::base::Camera> smartin::utils::CreateCamera(float fov, float aspect, const glm::vec3& position, const glm::vec3& eulerAngles) {
    auto transform = std::make_shared<base::Transform>(position, glm::vec3(0.0f, 0.0f, 0.0f), eulerAngles);
    auto camera = std::make_shared<base::Camera>(transform);
    camera->fieldOfView = fov;
    camera->aspect = aspect;

    holders::actors.Add(DEFAULT_CAMERA_NAME, camera);

    return camera;
}

void smartin::utils::DestroyActor(std::shared_ptr<smartin::base::Actor> actor) {
    actor->SetActive(false);
    holders::actors.Remove(actor);
}

// Assets
std::shared_ptr<smartin::graphics::Shader> smartin::utils::GetShader(const std::string& name) {
    return holders::shaders.Get(name);
}

std::shared_ptr<smartin::graphics::Shader> smartin::utils::CreateShader(const std::string& name) {
    std::shared_ptr<graphics::Shader> shader = nullptr;

    std::string vertexShaderPath = name + "." + VERTEX_SHADER_EXTENSION;
    std::string fragmentShaderPath = name + "." + FRAGMENT_SHADER_EXTENSION;
    shader = loaders::LoadShader(vertexShaderPath, fragmentShaderPath);

    if (shader != nullptr && shader->Compile() && shader->Validate())
        holders::shaders.Add(name, shader);
    else
        shader = nullptr;

    return shader;
}

void smartin::utils::DestroyShader(std::shared_ptr<smartin::graphics::Shader> shader) {
    holders::shaders.Remove(shader);
}

std::shared_ptr<smartin::graphics::Texture> smartin::utils::GetTexture(const std::string& name) {
    return holders::textures.Get(name);
}

std::shared_ptr<smartin::graphics::Texture> smartin::utils::CreateTexture(const std::string& name, const std::string& fileName) {
    auto texture = loaders::LoadTexture(fileName);

    if (texture != nullptr)
        holders::textures.Add(name, texture);

    return texture;
}

std::shared_ptr<smartin::graphics::Material> smartin::utils::GetMaterial(const std::string& name) {
    return holders::materials.Get(name);
}

std::shared_ptr<smartin::graphics::Material> smartin::utils::CreateMaterial(const std::string& name, const std::string& textureName, const glm::vec3& color, const std::string& shaderName) {
    std::shared_ptr<smartin::graphics::Material> material = nullptr;

    auto shader = GetShader(shaderName);
    if (shader != nullptr) {
        material = std::make_shared<graphics::Material>(shader);
        material->SetColor(color);

        auto texture = GetTexture(textureName);
        if (texture != nullptr)
            material->SetTexture(texture);
    }

    if (material != nullptr)
        holders::materials.Add(name, material);

    return material;
}

std::shared_ptr<smartin::graphics::Material> smartin::utils::CreateMaterial(const std::string& name, std::shared_ptr<smartin::graphics::Texture> texture) {
    std::shared_ptr<graphics::Material> material = std::make_shared<graphics::Material>(GetShader());

    if (texture != nullptr)
        material->SetTexture(texture);

    holders::materials.Add(name, material);

    return material;
}

std::shared_ptr<smartin::graphics::Skybox> smartin::utils::GetSkybox() {
    return holders::skybox;
}

std::shared_ptr<smartin::graphics::Skybox> smartin::utils::CreateSkybox(const std::array<std::string, 6>& faceTexturePaths) {
    auto shader = utils::GetShader(DEFAULT_SKY_SHADER_NAME);
    if (shader == nullptr)
        shader = utils::CreateShader(DEFAULT_SKY_SHADER_NAME);

    holders::skybox = loaders::LoadSkybox(faceTexturePaths, shader);
    return holders::skybox;
}

void smartin::utils::DestroySkybox() {
    holders::skybox = nullptr;
}

void smartin::utils::CollectGarbage() {
    holders::actors.CollectGarbage();
    holders::materials.CollectGarbage();
    holders::textures.CollectGarbage();
}
