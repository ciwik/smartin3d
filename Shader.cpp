#include "Shader.h"

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
    GLint result = 0; GLchar log[1024] = { 0 };
    glGetShaderiv(shaderProgramId, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shaderProgramId, sizeof(log), NULL, log);
        utils::log::E("Shader", "Error validating shader program: ");    // TODO
        return;
    }
}

void smartin::graphics::Shader::Apply() {
    glUseProgram(shaderProgramId);
}

void smartin::graphics::Shader::Destroy() {
    if (shaderProgramId != 0) {
        glDeleteProgram(shaderProgramId);
        shaderProgramId = 0;
    }

    vertexCode.clear();
    fragmentCode.clear();
}

void smartin::graphics::Shader::SetFloat(const char *variable, GLfloat value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform1f(uniformLocation, value);
}

void smartin::graphics::Shader::SetVector3(const char *variable, glm::vec3 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void smartin::graphics::Shader::SetVector4(const char *variable, glm::vec4 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}

void smartin::graphics::Shader::SetMatrix(const char *variable, glm::mat4 value) {
    GLuint uniformLocation = glGetUniformLocation(shaderProgramId, variable);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

smartin::graphics::Shader::~Shader() {
    Destroy();
}

void smartin::graphics::Shader::AddShader(std::string shaderCode, GLenum shaderType) {
    GLuint shaderId = glCreateShader(shaderType);
    const GLchar* code[1]; code[0] = shaderCode.c_str();
    GLint codeLength[1] = { (int)shaderCode.size() };
    glShaderSource(shaderId, 1, code, codeLength);
    glCompileShader(shaderId);
    glLinkProgram(shaderId);

    GLint result = 0; GLchar log[1024] = { 0 };
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shaderId, sizeof(log), NULL, log);
        utils::log::E("Shader", "Error compiling shader: ");    // TODO
        return;
    }

    glAttachShader(shaderProgramId, shaderId);
}

void smartin::graphics::Shader::CompileProgram() {
    glLinkProgram(shaderProgramId);

    GLint result = 0; GLchar log[1024] = { 0 };
    glGetShaderiv(shaderProgramId, GL_LINK_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shaderProgramId, sizeof(log), NULL, log);
        utils::log::E("Shader", "Error linking shader program: ");    // TODO
        return;
    }
}

smartin::graphics::Shader* smartin::graphics::ReadShaderFromFiles(const char *vertexCodePath, const char *fragmentCodePath) {
    std::string vertexCode = utils::io::ReadFile(vertexCodePath);
    std::string fragmentCode = utils::io::ReadFile(fragmentCodePath);

    Shader* shader = new Shader(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}
