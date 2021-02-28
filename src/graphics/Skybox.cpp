#include "graphics/Skybox.h"

// TODO: Move out of here
const GLfloat skyboxMeshVertices[] = {
        // X     Y     Z		  U	   V		 Xn	   Yn	 Zn
        -1.0f,  1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

        -1.0f,  1.0f,  1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
         1.0f,  1.0f,  1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f
};

const unsigned int skyboxMeshIndices[] = {
        // front
        0, 1, 2,
        2, 1, 3,
        // right
        2, 3, 5,
        5, 3, 7,
        // back
        5, 7, 4,
        4, 7, 6,
        // left
        4, 6, 0,
        0, 6, 1,
        // top
        4, 0, 5,
        5, 0, 2,
        // bottom
        1, 6, 3,
        3, 6, 7
};

smartin::graphics::Skybox::Skybox(int _width, int _height) {
    width = _width;
    height = _height;
}

bool smartin::graphics::Skybox::Load(const std::array<unsigned char*, 6> &facesImageData, std::shared_ptr<smartin::graphics::Shader> _shader) {
    shader = _shader;
    if (shader == nullptr)
        return false;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    for (size_t i = 0; i < facesImageData.size(); i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, facesImageData[i]);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    mesh = std::make_unique<Mesh>();
    mesh->Init(skyboxMeshVertices, skyboxMeshIndices, 64, 36);

    return true;
}

void smartin::graphics::Skybox::Apply(GLuint textureUnit, const glm::mat4& _view, const glm::mat4& projection) {
    glDepthMask(GL_FALSE);

    glm::mat4 view = glm::mat4(glm::mat3(_view));

    shader->Apply();
    shader->SetMatrix("projection", projection);
    shader->SetMatrix("view", view);

    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    mesh->Render();

    glDepthMask(GL_TRUE);
}

smartin::graphics::Skybox::~Skybox() {
    glDeleteTextures(1, &id);
}
