#include "utils/ModelLoader.h"

smartin::utils::ModelLoader::ModelLoader(const std::string& _filePath) : filePath(_filePath) { }

void smartin::utils::ModelLoader::Load() {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (scene == nullptr) {
        utils::log::E("ModelLoader", "Failed to load by path: " + filePath + ":\n" + importer.GetErrorString());
        return;
    }

    LoadNode(scene->mRootNode, scene);
    LoadMaterials(scene);
}

smartin::utils::ModelLoader::~ModelLoader() {
    meshes.clear();
    meshToMaterial.clear();
    textures.clear();
}

void smartin::utils::ModelLoader::LoadNode(aiNode* node, const aiScene* scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++)
        LoadMesh(scene->mMeshes[node->mMeshes[i]]);

    for (size_t i = 0; i < node->mNumChildren; i++)
        LoadNode(node->mChildren[i], scene);
}

void smartin::utils::ModelLoader::LoadMesh(aiMesh* mesh) {
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

    auto newMesh = std::make_unique<graphics::Mesh>();
    newMesh->Init(&vertices[0], &indices[0], vertices.size(), indices.size());
    meshes.push_back(std::move(newMesh));
    meshToMaterial.push_back(mesh->mMaterialIndex);
}

void smartin::utils::ModelLoader::LoadMaterials(const aiScene* scene) {
    textures.resize(scene->mNumMaterials);
    materialNames.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];

        aiString aiMaterialName;
        if (material->Get(AI_MATKEY_NAME, aiMaterialName) == AI_SUCCESS)
            materialNames[i] = std::string(aiMaterialName.C_Str());

        textures[i] = nullptr;
        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString aiTexturePath;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexturePath) == AI_SUCCESS) {
                int idx = std::string(aiTexturePath.data).rfind("\\");
                std::string fileName = std::string(aiTexturePath.data).substr(idx + 1);

                textures[i] = GetTexture(fileName);
                if (textures[i] == nullptr)
                    textures[i] = CreateTexture(fileName, fileName);
            }
        }
    }
}

void smartin::utils::ModelLoader::ApplyToActor(std::shared_ptr<base::Actor> actor) const {
    auto defaultColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    bool hasTextures = false;
    for (int i = 0; i < textures.size(); i++) {
        if (textures[i] != nullptr) {
            hasTextures = true;
            break;
        }
    }

    for (int i = 0; i < meshes.size(); i++) {
        unsigned int textureIdx = meshToMaterial[i];
        auto texture = textures[textureIdx];

        std::string materialName = materialNames[textureIdx];
        auto material = utils::GetMaterial(materialName);
        if (material == nullptr)
            material = utils::CreateMaterial(materialName, texture);

        if (!hasTextures)
            material->SetColor(defaultColor);

        actor->AddAppearance(std::move(meshes[i]), material);
    }
}
