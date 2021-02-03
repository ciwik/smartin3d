#include "TimeUtils.h"

float deltaTime;
float currentTime;
float lastTime;

void smartin::utils::time::Update(float time) {
    deltaTime = time - lastTime;
    lastTime = currentTime;
    currentTime = time;
}

float smartin::utils::time::GetDeltaTime() { return deltaTime; }
