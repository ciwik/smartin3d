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

    base::Actor* FindActor(std::string name);
    std::vector<base::Actor*> GetAllActors();

    base::Actor* CreateActor(std::string name,
                             glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
                             glm::vec3 eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    base::Actor* CreateActorWithAppearance(std::string name,
                                           std::string modelFileName = EMPTY,
                                           glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                                           glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
                                           glm::vec3 eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    base::Camera* CreateCamera(float fov, float aspect,
                               glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3 eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    void DestroyActor(std::string name);

    graphics::Shader* GetOrCreateShader(std::string name = DEFAULT_SHADER_NAME);
    void DestroyShader(std::string name);

    graphics::Texture* GetOrCreateTexture(std::string name);
    void DestroyTexture(std::string name);

    graphics::Material* GetOrCreateMaterial(std::string name,
                                            std::string textureName = EMPTY,
                                            glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f),
                                            std::string shaderName = DEFAULT_SHADER_NAME);
    void DestroyMaterial(std::string name);
}

#endif //SMARTIN3D_ASSETUTILS_H
