#ifndef SMARTIN3D_ASSETLOADER_H
#define SMARTIN3D_ASSETLOADER_H

#include <map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "base/Actor.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"

namespace smartin::utils::loader {
    graphics::Shader* GetShader(std::string name);
    graphics::Shader* LoadShaderFromFiles(std::string vertexCodePath, std::string fragmentCodePath);

    void LoadAppearenceForActor(base::Actor* actor, std::string modelName, std::string shaderName);
}

#endif //SMARTIN3D_ASSETLOADER_H
