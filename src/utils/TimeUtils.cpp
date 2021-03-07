#include "utils/TimeUtils.h"

static float deltaTime = 0.02f;
static float currentTime;
static float lastTime;
static int frameCount = 0;

void smartin::utils::time::Update() {
    float time = GetRealtimeSinceStartup();

    deltaTime = time - lastTime;
    lastTime = currentTime;
    currentTime = time;

    frameCount++;
}

float smartin::utils::time::GetDeltaTime() { return deltaTime; }

float smartin::utils::time::GetRealtimeSinceStartup() { return static_cast<float>(glfwGetTime()); }

int smartin::utils::time::GetFrameCount() { return frameCount; }
