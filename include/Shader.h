#ifndef SMARTIN3D_SHADER_H
#define SMARTIN3D_SHADER_H

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FileUtils.h"

namespace smartin::graphics {
    class Shader {
    public:
        Shader(std::string vertexCode, std::string fragmentCode);

        void Compile();
        void Validate();
        void Apply();
        void Destroy();

        void SetFloat(const char *variable, GLfloat value);
        void SetVector3(const char *variable, glm::vec3 value);
        void SetVector4(const char *variable, glm::vec4 value);
        void SetMatrix(const char *variable, glm::mat4 value);

        ~Shader();

private:
        void AddShader(std::string shaderCode, GLenum shaderType);
        void CompileProgram();

        bool CheckShaderStatus(GLuint shaderId, GLenum checkType, std::string tag);
        bool CheckProgramStatus(GLuint programId, GLenum checkType, std::string tag);

        std::string vertexCode;
        std::string fragmentCode;

        GLuint shaderProgramId;
    };

    Shader* ReadShaderFromFiles(const char *vertexCodePath, const char *fragmentCodePath);
}

#endif //SMARTIN3D_SHADER_H