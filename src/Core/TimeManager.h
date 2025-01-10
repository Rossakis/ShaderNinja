#pragma once

#include <CommonIncludes.h>

class TimeManager {
public:
    TimeManager();
    ~TimeManager();
    void UpdateTime();
    float GetDeltaTime() const; // const member function (const is declared after func name) means the class members won't be changed by this func
    
private:
    float m_lastTimeStamp;
    float m_deltaTime;
};