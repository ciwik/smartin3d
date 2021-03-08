#ifndef SMARTIN3D_TIMEUTILS_H
#define SMARTIN3D_TIMEUTILS_H

#include "precompiled.h"

namespace smartin::utils::time {
    float GetDeltaTime();
    std::chrono::time_point<std::chrono::system_clock> GetRealtimeSinceStartup();
    int GetFrameCount();

    void Update();
}

#endif //SMARTIN3D_TIMEUTILS_H
