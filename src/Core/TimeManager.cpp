#include <TimeManager.h>

TimeManager::TimeManager() : m_deltaTime(0.0f), m_lastTimeStamp(0.0f) {}

void TimeManager::UpdateTime() {
    m_deltaTime = glfwGetTime() - m_lastTimeStamp;
    m_lastTimeStamp = glfwGetTime();
}

float TimeManager::GetDeltaTime() const {
    return m_deltaTime;
}