#include "graphics/Shader.h"

smartin::graphics::Shader::Shader(const std::string& _vertexCode, const std::string& _fragmentCode) {
    vertexCode = _vertexCode;
    fragmentCode = _fragmentCode;
    shaderProgramId = 0;
}

bool smartin::graphics::Shader::Compile() {
    shaderProgramId = glCreateProgram();
    if (!shaderProgramId) {
        utils::log::E("Shader", "Error creating shader program");
        return false;
    }

    if (!AddShader(vertexCode, GL_VERTEX_SHADER))
        return false;
    if (!AddShader(fragmentCode, GL_FRAGMENT_SHADER))
        return false;

    if (!CompileProgram())
        return false;

    vertexCode.clear();
    fragmentCode.clear();

    return true;
}

bool smartin::graphics::Shader::Validate() {
    return CheckProgramStatus(shaderProgramId, GL_VALIDATE_STATUS, "validate");
}

void smartin::graphics::Shader::Apply() {
    glUseProgram(shaderProgramId);
}

void smartin::graphics::Shader::SetFloat(const char* variable, GLfloat value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform1f(uniformLocation, value);
}

void smartin::graphics::Shader::SetVector3(const char* variable, glm::vec3 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void smartin::graphics::Shader::SetVector4(const char* variable, glm::vec4 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}

void smartin::graphics::Shader::SetMatrix(const char* variable, glm::mat4 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
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
        utils::log::E("Shader", "Couldn't " + tag + ": " + std::to_string(result) + "\n" + std::string(log));
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
        utils::log::E("Shader", "Couldn't " + tag + ": " + std::to_string(result) + "\n" + std::string(log));
        return false;
    }

    return true;
}

void smartin::graphics::Shader::SetActiveTextureUnit(const char* variable, GLuint textureUnit) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform1i(uniformLocation, textureUnit);
}

void smartin::graphics::DisableShaders() {
    glUseProgram(0);
}
