#include "utils/Exceptions.h"

smartin::utils::error::SmartinRuntimeException::SmartinRuntimeException(std::string _tag, std::string _message) :
    std::runtime_error(_message),
    tag(_tag),
    message(_message) { }

const char* smartin::utils::error::SmartinRuntimeException::what() const {
    std::string whatMessage = "[" + tag + "]: " + message + "\n";
    return whatMessage.c_str();
}

smartin::utils::error::AssetException::AssetException(std::string message) :
    SmartinRuntimeException("Asset", message) { }

smartin::utils::error::FileNotFoundException::FileNotFoundException(std::string message) :
    SmartinRuntimeException("File", message) { }

smartin::utils::error::OpenGLException::OpenGLException(std::string message) :
    SmartinRuntimeException("OpenGL", message) { }

smartin::utils::error::ShaderException::ShaderException(std::string message) :
    SmartinRuntimeException("Shader", message) { }