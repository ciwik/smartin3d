#ifndef SMARTIN3D_MODEL3D_H
#define SMARTIN3D_MODEL3D_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "graphics/Mesh.h"
#include "Texture.h"
#include "graphics/Material.h"
#include "utils/Log.h"

namespace smartin::graphics {
    class Model3D {
    public:
        Model3D(std::string filePath);

        void Load();
        void Render();

        ~Model3D();

    private:
        void LoadNode(aiNode* node, const aiScene* scene);
        void LoadMesh(aiMesh* mesh, const aiScene* scene);
        void LoadMaterials(const aiScene* scene);

        std::vector<Mesh*> meshes;
        std::vector<Texture*> textures;
        std::vector<unsigned int> meshToTexture;

        std::string filePath;
    };
}

#endif //SMARTIN3D_MODEL3D_H
