#ifndef SMARTIN3D_MODEL3D_H
#define SMARTIN3D_MODEL3D_H

#include "precompiled.h"

#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "utils/AssetLoader.h"
#include "utils/AssetUtils.h"
#include "utils/Log.h"

namespace smartin::utils {
    class ModelLoader final {
    public:
        ModelLoader(const std::string& filePath);

        void Load();
        void ApplyToActor(std::shared_ptr<base::Actor> actor) const;

        ~ModelLoader();

    private:
        void LoadNode(aiNode* node, const aiScene* scene);
        void LoadMesh(aiMesh* mesh);
        void LoadMaterials(const aiScene* scene);

        mutable std::vector<std::unique_ptr<graphics::Mesh>> meshes;
        std::vector<std::shared_ptr<graphics::Texture>> textures;
        std::vector<unsigned int> meshToMaterial;
        std::vector<std::string> materialNames;

        std::string filePath;
    };
}

#endif //SMARTIN3D_MODEL3D_H
