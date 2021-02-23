#ifndef SMARTIN3D_MODEL3D_H
#define SMARTIN3D_MODEL3D_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "utils/AssetLoader.h"
#include "utils/AssetUtils.h"
#include "utils/Log.h"

namespace smartin::utils {
    class ModelLoader {
    public:
        ModelLoader(const std::string& filePath);

        void Load();
        void ConvertToAppearances(std::vector<graphics::Appearance*>& appearances);

        ~ModelLoader();

    private:
        void LoadNode(aiNode* node, const aiScene* scene);
        void LoadMesh(aiMesh* mesh, const aiScene* scene);
        void LoadMaterials(const aiScene* scene);

        std::vector<graphics::Mesh*> meshes;
        std::vector<graphics::Texture*> textures;
        std::vector<unsigned int> meshToTexture;

        std::string filePath;
    };
}

#endif //SMARTIN3D_MODEL3D_H
