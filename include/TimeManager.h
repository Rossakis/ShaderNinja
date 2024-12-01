#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

class TimeManager {
public:
    static TimeManager& instance() {
        static TimeManager INSTANCE;
        return INSTANCE;
    }    
    void updateTime();
    float getDeltaTime() const; // const member function (const is declared after func name) means the class members won't be changed by this func
    
private:
    TimeManager();
    TimeManager(const TimeManager&) = delete; // Deletes copy constructor
    TimeManager& operator=(const TimeManager&) = delete; // Deletes copy assignment operator

    float lastTimeStamp;
    float deltaTime;
};