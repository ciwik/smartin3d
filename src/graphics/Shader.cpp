#include "graphics/Shader.h"

smartin::graphics::Shader::Shader(const std::string& _vertexCode, const std::string& _fragmentCode) :
    vertexCode(_vertexCode),
    fragmentCode(_fragmentCode),
    shaderProgramId(0) { }

void smartin::graphics::Shader::Compile() {
    shaderProgramId = glCreateProgram();
    if (shaderProgramId == 0)
        throw utils::error::ShaderException("Error creating shader program");

    if (!AddShader(vertexCode, GL_VERTEX_SHADER))
        throw utils::error::ShaderException("Error creating vertex shader");
    if (!AddShader(fragmentCode, GL_FRAGMENT_SHADER))
        throw utils::error::ShaderException("Error creating fragment shader");

    if (!CompileProgram())
        throw utils::error::ShaderException("Error compiling shader program");

    vertexCode.clear();
    fragmentCode.clear();
}

bool smartin::graphics::Shader::Validate() {
    return CheckProgramStatus(shaderProgramId, GL_VALIDATE_STATUS, "validate");
}

void smartin::graphics::Shader::Apply() {
    glUseProgram(shaderProgramId);
}

void smartin::graphics::Shader::SetFloat(const std::string& variable, GLfloat value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable.c_str());
    glUniform1f(uniformLocation, value);
}

void smartin::graphics::Shader::SetVector3(const std::string& variable, glm::vec3 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable.c_str());
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void smartin::graphics::Shader::SetVector4(const std::string& variable, glm::vec4 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable.c_str());
    glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}

void smartin::graphics::Shader::SetMatrix(const std::string& variable, glm::mat4 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void smartin::graphics::Shader::SetActiveTextureUnit(const std::string& variable, GLuint textureUnit) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable.c_str());
    glUniform1i(uniformLocation, textureUnit);
}

smartin::graphics::Shader::~Shader() {
    if (shaderProgramId != 0) {
        glDeleteProgram(shaderProgramId);
        shaderProgramId = 0;
    }

    vertexCode.clear();
    fragmentCode.clear();
}

bool smartin::graphics::Shader::AddShader(const std::string& shaderCode, GLenum shaderType) {
    GLuint shaderId = glCreateShader(shaderType);
    const GLchar* code[1]; code[0] = shaderCode.c_str();
    GLint codeLength[1] = { (int)shaderCode.size() };
    glShaderSource(shaderId, 1, code, codeLength);
    glCompileShader(shaderId);
    glLinkProgram(shaderId);

    if (!CheckShaderStatus(shaderId, GL_COMPILE_STATUS, "compile"))
        return false;

    glAttachShader(shaderProgramId, shaderId);
    return true;
}

bool smartin::graphics::Shader::CompileProgram() {
    glLinkProgram(shaderProgramId);

    return CheckProgramStatus(shaderProgramId, GL_LINK_STATUS, "link");
}

bool smartin::graphics::Shader::CheckShaderStatus(GLuint id, GLenum checkType, const std::string& tag) {
    GLint result = 0;
    glGetShaderiv(id, checkType, &result);
    if (result != GL_TRUE) {
        GLchar log[1024] = { 0 };
        glGetShaderInfoLog(id, sizeof(log), NULL, log);
        utils::log::W("Shader", "Couldn't " + tag + ": " + std::to_string(result) + "\n" + std::string(log));
        return false;
    }

    return true;
}

bool smartin::graphics::Shader::CheckProgramStatus(GLuint id, GLenum checkType, const std::string& tag) {
    GLint result = 0;
    glGetProgramiv(id, checkType, &result);
    if (result != GL_TRUE) {
        GLchar log[1024] = { 0 };
        glGetProgramInfoLog(id, sizeof(log), NULL, log);
        utils::log::W("Shader", "Couldn't " + tag + ": " + std::to_string(result) + "\n" + std::string(log));
        return false;
    }

    return true;
}

void smartin::graphics::DisableShaders() {
    glUseProgram(0);
}
