#include "utils/AssetLoader.h"

const std::string MODELS_DIR = "models";
const std::string TEXTURES_DIR = "textures";
const std::string SHADERS_DIR = "shaders";

const std::string VERTEX_SHADER_EXTENSION = "vshader";
const std::string FRAGMENT_SHADER_EXTENSION = "fshader";

class Model3D {
public:
    Model3D(std::string filePath);

    void Load(smartin::graphics::Shader* shader);
    std::map<smartin::graphics::Mesh*, smartin::graphics::Material*> GetResult() const;

    ~Model3D();

private:
    void LoadNode(aiNode* node, const aiScene* scene);
    void LoadMesh(aiMesh* mesh, const aiScene* scene);
    void LoadMaterials(const aiScene* scene);

    std::vector<smartin::graphics::Mesh*> meshes;
    std::vector<smartin::graphics::Material*> materials;
    std::vector<unsigned int> meshToMaterial;

    std::string filePath;
};

void smartin::utils::loader::LoadAppearenceForActor(smartin::base::Actor* actor, std::string modelName, std::string shaderName) {
    smartin::graphics::Shader* shader = GetShader(shaderName);

    Model3D* model = new Model3D(MODELS_DIR + "/" + modelName);
    model->Load(shader);
    actor->SetAppearence(model->GetResult());
    delete model;
}

std::map<std::string, smartin::graphics::Shader*> loadedShaders;

smartin::graphics::Shader* smartin::utils::loader::GetShader(std::string name) {
    if (loadedShaders.find(name) == loadedShaders.end()) {
        std::string vertexShaderPath = SHADERS_DIR + "/" + name + "." + VERTEX_SHADER_EXTENSION;
        std::string fragmentShaderPath = SHADERS_DIR + "/" + name + "." + FRAGMENT_SHADER_EXTENSION;

        smartin::graphics::Shader* shader = LoadShaderFromFiles(vertexShaderPath, fragmentShaderPath);
        if (shader != nullptr) {
            shader->Compile();
            loadedShaders[name] = shader;
        }
    }

    return loadedShaders[name];
}

smartin::graphics::Shader* smartin::utils::loader::LoadShaderFromFiles(std::string vertexCodePath, std::string fragmentCodePath) {
    std::string vertexCode = utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = utils::io::ReadFile(fragmentCodePath);

    smartin::graphics::Shader* shader = new smartin::graphics::Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

Model3D::Model3D(std::string _filePath) {
    filePath = _filePath;
}

void Model3D::Load(smartin::graphics::Shader* shader) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (scene == nullptr) {
        smartin::utils::log::E("AssetLoader", "Failed to load by path: " + filePath + ":\n" + importer.GetErrorString());
        return;
    }

    LoadNode(scene->mRootNode, scene);

    materials.resize(scene->mNumMaterials);
    for (int i = 0; i < materials.size(); i++)
        materials[i] = new smartin::graphics::Material(shader);
    LoadMaterials(scene);
}

Model3D::~Model3D() { }

void Model3D::LoadNode(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++)
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);

    for (size_t i = 0; i < node->mNumChildren; i++)
        LoadNode(node->mChildren[i], scene);
}

void Model3D::LoadMesh(aiMesh *mesh, const aiScene *scene) {
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
    meshes.push_back(newMesh);
    meshToMaterial.push_back(mesh->mMaterialIndex);
}

void Model3D::LoadMaterials(const aiScene *scene) {
    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];

        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                int idx = std::string(path.data).rfind("\\");
                std::string fileName = std::string(path.data).substr(idx + 1);

                std::string texPath = TEXTURES_DIR + "/" + fileName;
                smartin::graphics::Texture* texture = new smartin::graphics::Texture(texPath.c_str());

                if (!texture->Load()) {
                    smartin::utils::log::E("AssetLoader", "Failed to load by path: " + texPath);
                    delete texture;
                } else {
                    materials[i]->SetTexture(texture);
                }
            }
        }
    }
}

std::map<smartin::graphics::Mesh*, smartin::graphics::Material*> Model3D::GetResult() const {
    std::map<smartin::graphics::Mesh*, smartin::graphics::Material*> result;

    for (int i = 0; i < meshes.size(); i++) {
        unsigned int idx = meshToMaterial[i];
        result[meshes[i]] = materials[idx];
    }

    return result;
}
