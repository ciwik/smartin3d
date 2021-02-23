#include "utils/AssetLoader.h"



smartin::graphics::Texture* smartin::utils::loaders::LoadTexture(const std::string &filePath) {
    smartin::graphics::Texture* texture = nullptr;

    int width, height, depth;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &depth, 0);
    if (data != nullptr) {
        texture = new smartin::graphics::Texture(width, height, depth);
        texture->Load(data);
        stbi_image_free(data);
    }

    return texture;
}

smartin::graphics::Shader* smartin::utils::loaders::LoadShader(const std::string &vertexCodePath, const std::string &fragmentCodePath) {
    std::string vertexCode = smartin::utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = smartin::utils::io::ReadFile(fragmentCodePath);

    smartin::graphics::Shader* shader = new smartin::graphics::Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

smartin::graphics::Material* LoadMaterial(unsigned int materialId, const aiScene* scene, smartin::graphics::Shader* shader);
smartin::graphics::Appearance* LoadAppearanceFromFile(aiMesh* mesh, const aiScene* scene, smartin::graphics::Shader* shader, std::vector<smartin::graphics::Material*> const &materials);
void LoadNode(smartin::graphics::Appearance* root, aiNode *node, const aiScene *scene, smartin::graphics::Shader* shader, std::vector<smartin::graphics::Material*> const &materials);

smartin::graphics::Appearance* smartin::utils::loaders::LoadAppearance(const std::string &modelFilePath, graphics::Shader* shader) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (scene == nullptr) {
        smartin::utils::log::E("AssetUtils", "Failed to load model by path: " + modelFilePath + ":\n" + importer.GetErrorString());
        return nullptr;
    }

    std::vector<smartin::graphics::Material*> materials(scene->mNumMaterials);
    for (int i = 0; i < scene->mNumMaterials; i++)
        materials[i] = LoadMaterial(i, scene, shader);

    smartin::graphics::Appearance* root = new smartin::graphics::Appearance(nullptr, nullptr);
    LoadNode(root, scene->mRootNode, scene, shader, materials);

    return root;
}

void LoadNode(smartin::graphics::Appearance* root, aiNode *node, const aiScene *scene, smartin::graphics::Shader* shader, std::vector<smartin::graphics::Material*> const &materials) {
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        smartin::graphics::Appearance* appearance = LoadAppearanceFromFile(scene->mMeshes[node->mMeshes[i]], scene, shader, materials);
        if (appearance != nullptr)
            root->children.push_back(appearance);
    }

    smartin::graphics::Appearance* newRoot = root;
    if (!root->children.empty())
        newRoot = root->children[0];

    for (size_t i = 0; i < node->mNumChildren; i++)
        LoadNode(newRoot, node->mChildren[i], scene, shader, materials);
}

smartin::graphics::Appearance* LoadAppearanceFromFile(aiMesh* mesh, const aiScene* scene, smartin::graphics::Shader* shader, std::vector<smartin::graphics::Material*> const &materials) {
    smartin::graphics::Material* material = nullptr;
    if (materials.size() > mesh->mMaterialIndex)
        material = materials[mesh->mMaterialIndex];

    if (material == nullptr)
        return nullptr;

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

    smartin::graphics::Mesh* newMesh = new smartin::graphics::Mesh();
    newMesh->Init(&vertices[0], &indices[0], vertices.size(), indices.size());

    return new smartin::graphics::Appearance(newMesh, material);
}

smartin::graphics::Material* LoadMaterial(unsigned int materialId, const aiScene* scene, smartin::graphics::Shader* shader) {
    aiMaterial* material = scene->mMaterials[materialId];
    if (material == nullptr)
        return nullptr;

    std::string textureName = "";
    smartin::graphics::Texture* texture = nullptr;
    if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
        aiString path;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
            int idx = std::string(path.data).rfind("\\");
            std::string filePath = smartin::utils::loaders::TEXTURE_DIR + "/" + std::string(path.data).substr(idx + 1);
            texture = smartin::utils::loaders::LoadTexture(filePath);
        }
    }

    smartin::graphics::Material* result = nullptr;

    if (texture != nullptr) {
        result = new smartin::graphics::Material(shader);
        result->SetTexture(texture);
    }

    return result;
}