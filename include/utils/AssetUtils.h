#ifndef SMARTIN3D_ASSETUTILS_H
#define SMARTIN3D_ASSETUTILS_H

#include <array>
#include <string>
#include <vector>

#include "base/Actor.h"
#include "base/Camera.h"
#include "graphics/Material.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "utils/External.h"

namespace smartin::utils {
    const std::string DEFAULT_SHADER_NAME = "default";
    const std::string EMPTY = "";

    base::Actor* CreateActor(std::string modelFilePath = EMPTY,
                             glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
                             glm::vec3 eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    base::Camera* CreateCamera(float fov, float aspect,
                               glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3 eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

    graphics::Shader* GetOrCreateShader(std::string name = DEFAULT_SHADER_NAME);
    graphics::Texture* GetOrCreateTexture(std::string name);
    graphics::Material* GetOrCreateMaterial(std::string name,
                                            std::string textureName = EMPTY,
                                            glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f),
                                            std::string shaderName = DEFAULT_SHADER_NAME);
}

#endif //SMARTIN3D_ASSETUTILS_H
