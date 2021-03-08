#ifndef SMARTIN3D_EXCEPTIONS_H
#define SMARTIN3D_EXCEPTIONS_H

namespace smartin::utils::error {
    struct SmartinRuntimeException : public std::runtime_error {
        std::string tag;
        std::string message;

        explicit SmartinRuntimeException(std::string tag, std::string message);
        const char* what() const override;
    };

    struct AssetException : public SmartinRuntimeException {
        explicit AssetException(std::string message);
    };

    struct FileNotFoundException : public SmartinRuntimeException {
        explicit FileNotFoundException(std::string message);
    };

    struct OpenGLException : public SmartinRuntimeException {
        explicit OpenGLException(std::string message);
    };

    struct ShaderException : public SmartinRuntimeException {
        explicit ShaderException(std::string message);
    };
}

#endif //SMARTIN3D_EXCEPTIONS_H
