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
        Shader(const char* vertexCode, const char* fragmentCode);

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
        void AddShader(const char* shaderCode, GLenum shaderType);
        void CompileProgram();

        const char* vertexCode;
        const char* fragmentCode;

        GLuint shaderProgramId;
    };

    Shader* ReadShaderFromFiles(const char *vertexCodePath, const char *fragmentCodePath);
}

#endif //SMARTIN3D_SHADER_H