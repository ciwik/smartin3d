#ifndef SMARTIN3D_TIMEUTILS_H
#define SMARTIN3D_TIMEUTILS_H

#include "precompiled.h"

using namespace std::chrono;

namespace smartin::utils::time {
    float GetDeltaTime();
    time_point<system_clock> GetRealtimeSinceStartup();
    int GetFrameCount();

    void Update();
}

#endif //SMARTIN3D_TIMEUTILS_H
