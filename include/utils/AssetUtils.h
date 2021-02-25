#ifndef SMARTIN3D_ASSETUTILS_H
#define SMARTIN3D_ASSETUTILS_H

#include <array>
#include <string>
#include <vector>

#include "base/Actor.h"
#include "base/Camera.h"
#include "graphics/Skybox.h"
#include "utils/AssetLoader.h"
#include "utils/AssetPool.h"

namespace smartin::utils {
    const std::string DEFAULT_SHADER_NAME = "default";
    const std::string DEFAULT_SKY_SHADER_NAME = "skybox";

    const std::string EMPTY = "";
    const std::string DEFAULT_CAMERA_NAME = "camera";

    const std::string VERTEX_SHADER_EXTENSION = "vshader";
    const std::string FRAGMENT_SHADER_EXTENSION = "fshader";

    base::Actor* FindActor(const std::string& name);
    std::vector<base::Actor*> GetAllActors();

    base::Actor* CreateActor(const std::string& name,
                             const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                             const glm::vec3& size = glm::vec3(1.0f, 1.0f, 1.0f),
                             const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    base::Actor* CreateActorWithAppearance(const std::string& name,
                                           const std::string& modelFileName = EMPTY,
                                           const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                                           const glm::vec3& size = glm::vec3(1.0f, 1.0f, 1.0f),
                                           const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    base::Camera* CreateCamera(float fov, float aspect,
                               const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                               const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    void DestroyActor(const std::string& name);

    graphics::Shader* GetShader(const std::string& name = DEFAULT_SHADER_NAME);
    graphics::Shader* CreateShader(const std::string& name = DEFAULT_SHADER_NAME);
    void DestroyShader(const std::string& name);

    graphics::Texture* GetTexture(const std::string& name);
    graphics::Texture* CreateTexture(const std::string& name, const std::string& fileName);
    void DestroyTexture(const std::string& name);

    graphics::Skybox* GetSkybox();
    graphics::Skybox* CreateSkybox(const std::array<std::string, 6>& faceTexturePaths);
    void DestroySkybox();

    graphics::Material* GetMaterial(const std::string& name);
    graphics::Material* CreateMaterial(const std::string& name,
                                       graphics::Texture* texture);
    graphics::Material* CreateMaterial(const std::string& name,
                                       const std::string& textureName = EMPTY,
                                       const glm::vec3& color = glm::vec3(0.0f, 0.0f, 0.0f),
                                       const std::string& shaderName = DEFAULT_SHADER_NAME);
    void DestroyMaterial(const std::string& name);

    namespace holders {
        static AssetPool<graphics::Texture> textures;
        static AssetPool<graphics::Material> materials;
        static AssetPool<graphics::Shader> shaders;
        static AssetPool<base::Actor> actors;
        static graphics::Skybox* skybox;
    }
}

#endif //SMARTIN3D_ASSETUTILS_H
