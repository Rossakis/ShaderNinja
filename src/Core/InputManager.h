#pragma once

#include <TimeManager.h>
#include <CommonIncludes.h>

class InputManager {
public:
    InputManager(GLFWwindow& window, TimeManager& time);
    ~InputManager();
    
    void UpdateInput();
    glm::vec2 GetMouseDeltaRaw() const; //Uses unscaled mouse delta
    glm::vec2 GetMouseDelta() const; //Uses mouse delta that gets scaled by frame deltaTime
    
    bool UpPressed();
    bool DownPressed();
    bool LeftPressed();
    bool RightPressed();
    bool ForwardPressed();
    bool BackwardsPressed();
    bool SpeedUpPressed();
    bool PausePressed();

private:
    bool pressedEdit;
    GLFWwindow& m_window;
    TimeManager& m_time;
    double m_lastPosX;
    double m_lastPosY;
    glm::vec2 m_lastMousePos;
    glm::vec2 m_mouseDeltaPos;
};