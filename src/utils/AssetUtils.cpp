#include "utils/AssetUtils.h"

const std::string TEXTURE_DIR = "textures";
const std::array<std::string, 3> SUPPORTED_TEXTURE_FORMATS = { "tga", "png", "jpg" };

const std::string SHADER_DIR = "shaders";
const std::string VERTEX_SHADER_EXTENSION = "vshader";
const std::string FRAGMENT_SHADER_EXTENSION = "fshader";

const std::string MODEL_DIR = "models";

namespace loaders {
    smartin::graphics::Texture* LoadTexture(std::string filePath);
    smartin::graphics::Shader* LoadShader(std::string vertexCodePath, std::string fragmentCodePath);

    smartin::graphics::Appearance* LoadAppearance(std::string modelFilePath, smartin::graphics::Shader* shader);
}

namespace holders {
    smartin::utils::AssetPool<smartin::graphics::Texture>* textures;
    smartin::utils::AssetPool<smartin::graphics::Material>* materials;
    smartin::utils::AssetPool<smartin::graphics::Shader>* shaders;
    smartin::utils::AssetPool<smartin::base::Actor>* actors;
}

// Actors
smartin::base::Actor* smartin::utils::FindActor(std::string name) {
    return holders::actors->Get(name);
}

smartin::base::Actor* smartin::utils::CreateActor(std::string name, glm::vec3 position, glm::vec3 size, glm::vec3 eulerAngles) {
    if (holders::actors->Get(name) != nullptr) {
        smartin::utils::log::E("AssetUtils", "Actor with the same name already exists: " + name);
        return nullptr;
    }

    base::Transform* transform = new base::Transform(position, size, eulerAngles);
    smartin::base::Actor* actor = new smartin::base::Actor(transform);
    holders::actors->Add(name, actor);

    return actor;
}

smartin::base::Actor* smartin::utils::CreateActorWithAppearance(std::string name, std::string modelFileName, glm::vec3 position, glm::vec3 size, glm::vec3 eulerAngles) {
    smartin::base::Actor* actor = CreateActor(name, position, size, eulerAngles);
    if (actor != nullptr) {
        std::string modelFilePath = MODEL_DIR + "/" + modelFileName;
        graphics::Appearance* appearance = loaders::LoadAppearance(modelFilePath, GetOrCreateShader(DEFAULT_SHADER_NAME)); // TODO
        actor->SetAppearance(appearance);
    }

    return actor;
}

std::vector<smartin::base::Actor*> smartin::utils::GetAllActors() {
    return holders::actors->GetAll();
}

smartin::base::Camera* smartin::utils::CreateCamera(float fov, float aspect, glm::vec3 position, glm::vec3 eulerAngles) {
    base::Transform* transform = new base::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), eulerAngles);
    base::Camera* camera = new base::Camera(transform);
    camera->fieldOfView = fov;
    camera->aspect = aspect;

    holders::actors->Add(DEFAULT_CAMERA_NAME, camera);

    return camera;
}


// Assets
std::string GetNameByPath(std::string const &path);

smartin::graphics::Shader* smartin::utils::GetOrCreateShader(std::string name) {
    smartin::graphics::Shader* result = nullptr;

    result = holders::shaders->Get(name);
    if (result == nullptr) {
        std::string vertexShaderPath = SHADER_DIR + "/" + name + "." + VERTEX_SHADER_EXTENSION;
        std::string fragmentShaderPath = SHADER_DIR + "/" + name + "." + FRAGMENT_SHADER_EXTENSION;

        result = loaders::LoadShader(vertexShaderPath, fragmentShaderPath);
        if (result != nullptr) {
            if (result->Compile() && result->Validate()) {
                holders::shaders->Add(name, result);
            } else {
                delete result;
                result = nullptr;
            }
        }
    }

    if (result == nullptr)
        utils::log::E("AssetUtils", "Failed to find shader: " + name);

    return result;
}

smartin::graphics::Texture* smartin::utils::GetOrCreateTexture(std::string name) {
    smartin::graphics::Texture* result = nullptr;

    std::string _name = GetNameByPath(name);
    result = holders::textures->Get(_name);
    if (result == nullptr) {
        std::string path = TEXTURE_DIR + "/" + name;

        result = loaders::LoadTexture(path);
        if (result == nullptr) {
            // Try to add all possible extensions
            for (std::string ext : SUPPORTED_TEXTURE_FORMATS) {
                std::string _path = path + "." + ext;
                result = loaders::LoadTexture(_path);
                if (result != nullptr)
                    break;
            }

            if (result != nullptr)
                holders::textures->Add(_name, result);
        }
    }

    if (result == nullptr)
        utils::log::E("AssetUtils", "Failed to find texture: " + name);

    return result;
}

smartin::graphics::Material* smartin::utils::GetOrCreateMaterial(std::string name, std::string textureName, glm::vec3 color, std::string shaderName) {
    smartin::graphics::Material* result = nullptr;

    result = holders::materials->Get(name);
    if (result == nullptr) {
        smartin::graphics::Shader* shader = GetOrCreateShader(shaderName);
        if (shader != nullptr) {
            result = new smartin::graphics::Material(shader);

            if (textureName.empty()) textureName = name;
            smartin::graphics::Texture* texture = GetOrCreateTexture(textureName);
            if (texture != nullptr)
                result->SetTexture(texture);

            result->SetColor(color);

            holders::materials->Add(name, result);
        }
    }

    if (result == nullptr)
        utils::log::E("AssetUtils", "Failed to find material: " + name);

    return result;
}

void smartin::utils::DestroyActor(std::string name) {
    holders::actors->Remove(name);
}

void smartin::utils::DestroyShader(std::string name) {
    holders::shaders->Remove(name);
}

void smartin::utils::DestroyTexture(std::string name) {
    holders::textures->Remove(name);
}

void smartin::utils::DestroyMaterial(std::string name) {
    holders::materials->Remove(name);
}


// Loaders
smartin::graphics::Texture* loaders::LoadTexture(std::string filePath) {
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

smartin::graphics::Shader* loaders::LoadShader(std::string vertexCodePath, std::string fragmentCodePath) {
    std::string vertexCode = smartin::utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = smartin::utils::io::ReadFile(fragmentCodePath);

    smartin::graphics::Shader* shader = new smartin::graphics::Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

static int materialCounter = 0;

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
            std::string filePath = TEXTURE_DIR + "/" + std::string(path.data).substr(idx + 1);
            texture = loaders::LoadTexture(filePath);

            textureName = GetNameByPath(filePath) + std::to_string(materialId) + std::to_string(materialCounter);
            holders::textures->Add(textureName, texture);
        }
    }

    smartin::graphics::Material* result = nullptr;

    if (texture != nullptr) {
        std::string materialName = textureName + std::to_string(materialCounter);
        result = new smartin::graphics::Material(shader);
        result->SetTexture(texture);
        holders::materials->Add(materialName, result);
        materialCounter++;
    }

    return result;
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

smartin::graphics::Appearance* loaders::LoadAppearance(std::string modelFilePath, smartin::graphics::Shader* shader) {
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

std::string GetNameByPath(std::string const &path) {
    int dotPosition = path.length() - 1;
    for (int i = path.length() - 1; i >= 0; i--) {
        if (path[i] == '.') {
            dotPosition = i;
            break;
        }
    }

    return path.substr(0, dotPosition + 1);
}
