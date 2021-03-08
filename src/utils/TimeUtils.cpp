#include "utils/TimeUtils.h"

using namespace std::chrono;

static float deltaTime;
static time_point<system_clock> currentTime;
static time_point<system_clock> lastTime;
static int frameCount = 0;

void smartin::utils::time::Update() {
    lastTime = currentTime;
    currentTime = GetRealtimeSinceStartup();

    auto delta = duration_cast<microseconds>(currentTime - lastTime);
    deltaTime = delta.count() / 1000000.0f;
    frameCount++;
}

float smartin::utils::time::GetDeltaTime() { return deltaTime; }

time_point<system_clock> smartin::utils::time::GetRealtimeSinceStartup() { return system_clock::now(); }

int smartin::utils::time::GetFrameCount() { return frameCount; }
