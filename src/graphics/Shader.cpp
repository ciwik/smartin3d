#include "graphics/Shader.h"

smartin::graphics::Shader::Shader(std::string _vertexCode, std::string _fragmentCode) {
    vertexCode = _vertexCode;
    fragmentCode = _fragmentCode;
    shaderProgramId = 0;
}

void smartin::graphics::Shader::Compile() {
    shaderProgramId = glCreateProgram();
    if (!shaderProgramId) {
        utils::log::E("Shader", "Error creating shader program");
        return;
    }

    AddShader(vertexCode, GL_VERTEX_SHADER);
    AddShader(fragmentCode, GL_FRAGMENT_SHADER);

    CompileProgram();

    vertexCode.clear();
    fragmentCode.clear();
}

void smartin::graphics::Shader::Validate() {
    CheckProgramStatus(shaderProgramId, GL_VALIDATE_STATUS, "validate");
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

void smartin::graphics::Shader::SetTexture(const char* variable, smartin::graphics::Texture* value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform1i(uniformLocation, value->id);
}

smartin::graphics::Shader::~Shader() {
    if (shaderProgramId != 0) {
        glDeleteProgram(shaderProgramId);
        shaderProgramId = 0;
    }

    vertexCode.clear();
    fragmentCode.clear();
}

void smartin::graphics::Shader::AddShader(std::string shaderCode, GLenum shaderType) {
    GLuint shaderId = glCreateShader(shaderType);
    const GLchar* code[1]; code[0] = shaderCode.c_str();
    GLint codeLength[1] = { (int)shaderCode.size() };
    glShaderSource(shaderId, 1, code, codeLength);
    glCompileShader(shaderId);
    glLinkProgram(shaderId);

    if (!CheckShaderStatus(shaderId, GL_COMPILE_STATUS, "compile"))
        return;

    glAttachShader(shaderProgramId, shaderId);
}

void smartin::graphics::Shader::CompileProgram() {
    glLinkProgram(shaderProgramId);

    if (!CheckProgramStatus(shaderProgramId, GL_LINK_STATUS, "link"))
        return;
}

bool smartin::graphics::Shader::CheckShaderStatus(GLuint id, GLenum checkType, std::string tag) {
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

bool smartin::graphics::Shader::CheckProgramStatus(GLuint id, GLenum checkType, std::string tag) {
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

smartin::graphics::Shader* smartin::graphics::ReadShaderFromFiles(const char *vertexCodePath, const char *fragmentCodePath) {
    std::string vertexCode = utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = utils::io::ReadFile(fragmentCodePath);

    Shader* shader = new Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

void smartin::graphics::DisableShaders() {
    glUseProgram(0);
}
