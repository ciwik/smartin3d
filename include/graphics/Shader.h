#ifndef SMARTIN3D_SHADER_H
#define SMARTIN3D_SHADER_H

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/FileUtils.h"
#include "Texture.h"

namespace smartin::graphics {
    class Shader {
    public:
        Shader(const std::string& vertexCode, const std::string& fragmentCode);

        bool Compile();
        bool Validate();
        void Apply();

        void SetFloat(const char* variable, GLfloat value);
        void SetVector3(const char* variable, glm::vec3 value);
        void SetVector4(const char* variable, glm::vec4 value);
        void SetMatrix(const char* variable, glm::mat4 value);
        void SetActiveTextureUnit(const char* variable, GLuint textureUnit);

        ~Shader();

private:
        bool AddShader(const std::string& shaderCode, GLenum shaderType);
        bool CompileProgram();

        bool CheckShaderStatus(GLuint shaderId, GLenum checkType, const std::string& tag);
        bool CheckProgramStatus(GLuint programId, GLenum checkType, const std::string& tag);

        std::string vertexCode;
        std::string fragmentCode;

        GLuint shaderProgramId;
    };

    void DisableShaders();
}

#endif //SMARTIN3D_SHADER_H