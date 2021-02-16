#include "graphics/Model3D.h"

smartin::graphics::Model3D::Model3D(std::string _filePath) {
    filePath = _filePath;
}

void smartin::graphics::Model3D::Load() {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (scene == nullptr) {
        utils::log::E("Model3D", "Failed to load by path: " + filePath + ":\n" + importer.GetErrorString());
        return;
    }

    LoadNode(scene->mRootNode, scene);
    LoadMaterials(scene);
}

void smartin::graphics::Model3D::Render() {
    for (size_t i = 0; i < meshes.size(); i++) {
        unsigned int textureIdx = meshToTexture[i];
        if (textureIdx < textures.size() && textures[textureIdx] != nullptr)
            textures[textureIdx]->Apply();

        meshes[i]->Render();
    }
}

smartin::graphics::Model3D::~Model3D() {
    for (size_t i = 0; i < meshes.size(); i++) {
        if (meshes[i]) {
            delete meshes[i];
            meshes[i] = nullptr;
        }
    }

    for (size_t i = 0; i < textures.size(); i++) {
        if (textures[i]) {
            delete textures[i];
            textures[i] = nullptr;
        }
    }
}

void smartin::graphics::Model3D::LoadNode(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++)
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);

    for (size_t i = 0; i < node->mNumChildren; i++)
        LoadNode(node->mChildren[i], scene);
}

void smartin::graphics::Model3D::LoadMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    // Vertices
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        // XYZ
        vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });

        // UV
        if (mesh->mTextureCoords[0])
            vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
        else
            vertices.insert(vertices.end(), { 0.0f, 0.0f });

        // Normals
        vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
    }

    // Faces
    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    Mesh* newMesh = new Mesh();
    newMesh->Init(&vertices[0], &indices[0], vertices.size(), indices.size());
    meshes.push_back(newMesh);
    meshToTexture.push_back(mesh->mMaterialIndex);
}

void smartin::graphics::Model3D::LoadMaterials(const aiScene *scene) {
    textures.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];
        textures[i] = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                int idx = std::string(path.data).rfind("\\");
                std::string fileName = std::string(path.data).substr(idx + 1);

                std::string texPath = std::string("Textures/") + fileName;
                textures[i] = new Texture(texPath.c_str());

                if (!textures[i]->Load()) {
                    printf("Texture '%s' can't be found", texPath.c_str());
                    delete textures[i];
                    textures[i] = nullptr;
                }
            }
        }
    }
}
