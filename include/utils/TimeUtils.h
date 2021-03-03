#ifndef SMARTIN3D_TIMEUTILS_H
#define SMARTIN3D_TIMEUTILS_H

#include "precompiled.h"

namespace smartin::utils::time {
    float GetDeltaTime();
    float GetRealtimeSinceStartup();
    int GetFrameCount();

    void Update();
}

#endif //SMARTIN3D_TIMEUTILS_H
