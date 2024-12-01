#pragma once

#include <TimeManager.h>
#include <glm/glm.hpp>

class InputManager {
public:
    static InputManager& instance() {
        static InputManager INSTANCE;
        return INSTANCE;
    }    
    void updateInput(GLFWwindow *window);
    //Uses unscaled mouse delta
    glm::vec2 getMouseDeltaRaw() const;
    //Uses mouse delta that gets scaled by frame deltaTime
    glm::vec2 getMouseDelta() const;

private:
    InputManager();
    InputManager(const InputManager&) = delete; // Deletes copy constructor
    InputManager& operator=(const InputManager&) = delete; // Deletes copy assignment operator

    double lastPosX;
    double lastPosY;
    glm::vec2 lastMousePos;
    glm::vec2 mouseDeltaPos;
};