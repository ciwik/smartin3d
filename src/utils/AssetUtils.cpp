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

    try {
        if (actor != nullptr)
            loaders::LoadAppearanceForActor(actor, modelFileName);
    } catch (error::SmartinRuntimeException& e) {
        utils::log::W("Asset", "Couldn't load appearence '" + modelFileName + "' for actor '" + name + "'");
    }

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

    holders::actors.Add(defaultCameraName, camera);

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
    try {
        std::shared_ptr<graphics::Shader> shader = nullptr;

        std::string vertexShaderPath = name + "." + vertexShaderExtension;
        std::string fragmentShaderPath = name + "." + fragmentShaderExtension;
        shader = loaders::LoadShader(vertexShaderPath, fragmentShaderPath);

        if (shader != nullptr) {
            shader->Compile();
            shader->Validate();
            holders::shaders.Add(name, shader);
        }
        return shader;
    } catch (error::ShaderException& e) {
        utils::log::E(e);
        return nullptr;
    }
}

void smartin::utils::DestroyShader(std::shared_ptr<smartin::graphics::Shader> shader) {
    holders::shaders.Remove(shader);
}

std::shared_ptr<smartin::graphics::Texture> smartin::utils::GetTexture(const std::string& name) {
    return holders::textures.Get(name);
}

std::shared_ptr<smartin::graphics::Texture> smartin::utils::CreateTexture(const std::string& name, const std::string& fileName) {
    std::shared_ptr<graphics::Texture> texture = nullptr;

    try {
        texture = loaders::LoadTexture(fileName);
    } catch (error::FileNotFoundException& e) {
        log::E(e);
    }

    if (texture != nullptr)
        holders::textures.Add(name, texture);

    return texture;
}

std::shared_ptr<smartin::graphics::Material> smartin::utils::GetMaterial(const std::string& name) {
    return holders::materials.Get(name);
}

std::shared_ptr<smartin::graphics::Material> smartin::utils::CreateMaterial(const std::string& name, const std::string& shaderName, const std::string& textureName, const glm::vec3& color) {
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
    std::shared_ptr<graphics::Material> material = std::make_shared<graphics::Material>(GetShader(graphics::defaultShaderName));

    if (texture != nullptr)
        material->SetTexture(texture);

    holders::materials.Add(name, material);

    return material;
}

std::shared_ptr<smartin::graphics::Skybox> smartin::utils::GetSkybox() {
    return holders::skybox;
}

std::shared_ptr<smartin::graphics::Skybox> smartin::utils::CreateSkybox(const std::array<std::string, 6>& faceTexturePaths) {
    auto shader = utils::GetShader(graphics::skyboxShaderName);
    if (shader == nullptr)
        shader = utils::CreateShader(graphics::skyboxShaderName);

    try {
        holders::skybox = loaders::LoadSkybox(faceTexturePaths, shader);
    } catch (error::SmartinRuntimeException& e) {
        log::E(e);
    }

    return holders::skybox;
}

void smartin::utils::DestroySkybox() {
    holders::skybox = nullptr;
}

std::shared_ptr<smartin::graphics::lighting::Light> smartin::utils::GetLight(const std::string& name) {
    return holders::lights.Get(name);
}

std::shared_ptr<smartin::graphics::lighting::Light> smartin::utils::GetMainLight() {
    return holders::mainLight;
}

std::vector<std::shared_ptr<smartin::graphics::lighting::Light>> smartin::utils::GetAllLights() {
    return holders::lights.GetAll();
}

std::shared_ptr<smartin::graphics::lighting::Light> smartin::utils::CreateDirectionalLight(const std::string &name, glm::vec3 color, glm::vec3 direction,
                                                                                           float ambientIntensity, float diffuseIntensity, bool main) {
    auto light = std::make_shared<graphics::lighting::DirectionalLight>(1024, 1024, color, direction, ambientIntensity, diffuseIntensity);
    holders::lights.Add(name, light);
    if (main)
        holders::mainLight = light;

    return light;
}

void smartin::utils::DestroyLight(std::shared_ptr<graphics::lighting::Light> light) {
    if (light == holders::mainLight)
        holders::mainLight = nullptr;
    holders::lights.Remove(light);
}

void smartin::utils::DebugPrintContent() {
    holders::actors.DebugPrintContent("Actors");
    holders::materials.DebugPrintContent("Materials");
    holders::lights.DebugPrintContent("Lights");
    holders::textures.DebugPrintContent("Textures");
    holders::shaders.DebugPrintContent("Shaders");
}

void smartin::utils::CollectGarbage() {
    holders::actors.CollectGarbage();
    holders::materials.CollectGarbage();
    holders::textures.CollectGarbage();
}
