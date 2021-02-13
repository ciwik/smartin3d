#include "utils/TimeUtils.h"

float deltaTime = 0.02f;
float currentTime;
float lastTime;
int frameCount = 0;

void smartin::utils::time::Update() {
    float time = glfwGetTime();

    deltaTime = time - lastTime;
    lastTime = currentTime;
    currentTime = time;

    frameCount++;
}

float smartin::utils::time::GetDeltaTime() { return deltaTime; }

float smartin::utils::time::GetRealtimeSinceStartup() { return glfwGetTime(); }

int smartin::utils::time::GetFrameCount() { return frameCount; }