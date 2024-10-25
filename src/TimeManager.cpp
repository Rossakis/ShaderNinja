#include <TimeManager.h>
#include <glfw/glfw3.h>

TimeManager::TimeManager() : deltaTime(0.0f), lastTimeStamp(0.0f) {}

void TimeManager::updateTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTimeStamp;
    lastTimeStamp = currentTime;
}

float TimeManager::getDeltaTime() const {
    return deltaTime;
}