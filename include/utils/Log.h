#ifndef SMARTIN3D_LOG_H
#define SMARTIN3D_LOG_H

#include <ostream>
#include <string>

namespace smartin::utils::log {
    void Init(std::ostream& out);

    void I(const std::string& tag, const std::string& message);
    void W(const std::string& tag, const std::string& message);
    void E(const std::string& tag, const std::string& message);
}

#endif //SMARTIN3D_LOG_H
