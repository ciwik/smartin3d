#ifndef SMARTIN3D_ASSETUTILS_H
#define SMARTIN3D_ASSETUTILS_H

#include <array>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "base/Actor.h"
#include "base/Camera.h"
#include "graphics/Appearance.h"
#include "graphics/Material.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "utils/External.h"
#include "utils/AssetPool.h"

namespace smartin::utils {
    const std::string DEFAULT_SHADER_NAME = "default";
    const std::string EMPTY = "";
    const std::string DEFAULT_CAMERA_NAME = "camera";

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
                               glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3 eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    void DestroyActor(const std::string& name);

    graphics::Shader* GetOrCreateShader(const std::string& name = DEFAULT_SHADER_NAME);
    void DestroyShader(const std::string& name);

    graphics::Texture* GetOrCreateTexture(const std::string& name);
    void DestroyTexture(const std::string& name);

    graphics::Material* GetOrCreateMaterial(const std::string& name,
                                            const std::string& textureName = EMPTY,
                                            const glm::vec3& color = glm::vec3(0.0f, 0.0f, 0.0f),
                                            const std::string& shaderName = DEFAULT_SHADER_NAME);
    void DestroyMaterial(const std::string& name);

    namespace holders {
        static AssetPool<graphics::Texture> textures;
        static AssetPool<graphics::Material> materials;
        static AssetPool<graphics::Shader> shaders;
        static AssetPool<base::Actor> actors;
    }
}

#endif //SMARTIN3D_ASSETUTILS_H
