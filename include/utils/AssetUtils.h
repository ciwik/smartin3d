#ifndef SMARTIN3D_ASSETUTILS_H
#define SMARTIN3D_ASSETUTILS_H

#include "precompiled.h"

#include "base/Actor.h"
#include "base/Camera.h"
#include "graphics/Skybox.h"
#include "utils/AssetLoader.h"
#include "utils/AssetPool.h"

namespace smartin::utils {
    static const std::string defaultCameraName = "camera";

    static const std::string vertexShaderExtension = "vshader";
    static const std::string fragmentShaderExtension = "fshader";

    void DebugPrintContent();
    void CollectGarbage();

    std::shared_ptr<base::Actor> FindActor(const std::string& name);
    std::vector<std::shared_ptr<base::Actor>> GetAllActors();

    std::shared_ptr<base::Actor> CreateActor(const std::string& name,
                                             const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                                             const glm::vec3& size = glm::vec3(1.0f, 1.0f, 1.0f),
                                             const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    std::shared_ptr<base::Actor> CreateActorWithAppearance(const std::string& name,
                                                           const std::string& modelFileName = "",
                                                           const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                                                           const glm::vec3& size = glm::vec3(1.0f, 1.0f, 1.0f),
                                                           const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    std::shared_ptr<base::Camera> CreateCamera(float fov, float aspect,
                                               const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                                               const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    void DestroyActor(std::shared_ptr<base::Actor> actor);

    std::shared_ptr<graphics::Shader> GetShader(const std::string& name);
    std::shared_ptr<graphics::Shader> CreateShader(const std::string& name);
    void DestroyShader(std::shared_ptr<graphics::Shader> shader);

    std::shared_ptr<graphics::Texture> GetTexture(const std::string& name);
    std::shared_ptr<graphics::Texture> CreateTexture(const std::string& name, const std::string& fileName);

    std::shared_ptr<graphics::Skybox> GetSkybox();
    std::shared_ptr<graphics::Skybox> CreateSkybox(const std::array<std::string, 6>& faceTexturePaths);
    void DestroySkybox();

    std::shared_ptr<graphics::Material> GetMaterial(const std::string& name);
    std::shared_ptr<graphics::Material> CreateMaterial(const std::string& name,
                                        std::shared_ptr<graphics::Texture> texture);
    std::shared_ptr<graphics::Material> CreateMaterial(const std::string& name,
                                        const std::string& shaderName,
                                        const std::string& textureName = "",
                                        const glm::vec3& color = glm::vec3(0.0f, 0.0f, 0.0f));

    namespace holders {
        static AssetPool<graphics::Texture> textures (true);
        static AssetPool<graphics::Material> materials (true);
        static AssetPool<graphics::Shader> shaders;
        static AssetPool<base::Actor> actors;
        static std::shared_ptr<graphics::Skybox> skybox;
    }
}

#endif //SMARTIN3D_ASSETUTILS_H
