#ifndef SMARTIN3D_SHADER_H
#define SMARTIN3D_SHADER_H

#include "precompiled.h"

#include "utils/FileUtils.h"
#include "Texture.h"

namespace smartin::graphics {
    class Shader final {
    public:
        Shader(const std::string& vertexCode, const std::string& fragmentCode);

        void Compile();
        bool Validate();
        void Apply();

        void SetFloat(const std::string& variable, GLfloat value);
        void SetVector3(const std::string& variable, glm::vec3 value);
        void SetVector4(const std::string& variable, glm::vec4 value);
        void SetMatrix(const std::string& variable, glm::mat4 value);
        void SetActiveTextureUnit(const std::string& variable, GLuint textureUnit);

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

    static const std::string unlitShaderName = "unlit";
    static const std::string directionalMapShaderName = "directional_shadow";
    static const std::string omniDirectionalMapShaderName = "omni_shadow";
    static const std::string skyboxShaderName = "skybox";
    static const std::string defaultShaderName = unlitShaderName;
}

#endif //SMARTIN3D_SHADER_H