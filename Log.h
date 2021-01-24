#ifndef SMARTIN3D_LOG_H
#define SMARTIN3D_LOG_H

#include <string>

namespace smartin::utils::log
{
    enum LOG_TYPE { ERROR = 0, WARNING = 1, INFO = 2 };

    void Write(const std::string tag, const std::string message, std::ostream &out, LOG_TYPE type = INFO) {
        out << "[" << tag << "]: " << message << "\n";
    }
}

#endif //SMARTIN3D_LOG_H