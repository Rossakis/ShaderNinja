#include <TimeManager.h>

TimeManager::TimeManager() : deltaTime(0.0f), lastTimeStamp(0.0f) {}

void TimeManager::updateTime() {
    deltaTime = glfwGetTime() - lastTimeStamp;
    lastTimeStamp = glfwGetTime();
}

float TimeManager::getDeltaTime() const {
    return deltaTime;
}