#ifndef SMARTIN3D_LOG_H
#define SMARTIN3D_LOG_H

#include "precompiled.h"

#include "Exceptions.h"

namespace smartin::utils::log {
    void Init(std::ostream& out);

    void I(const std::string& tag, const std::string& message);
    void W(const std::string& tag, const std::string& message);
    void E(const error::SmartinRuntimeException& exception);
}

#endif //SMARTIN3D_LOG_H
