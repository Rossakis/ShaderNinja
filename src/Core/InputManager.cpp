#include <InputManager.h>

InputManager::InputManager(GLFWwindow& window, TimeManager& time) : m_window (window), m_time (time)
{
    m_lastPosX = 0.0f;
    m_lastPosY = 0.0f;
    m_lastMousePos = glm::vec2(0.0f);
    m_mouseDeltaPos = glm::vec2(0.0f);
}

void InputManager::UpdateInput() {
    //Calculate input difference
    double mouseDeltaX, mouseDeltaY = 0.0f;
    glfwGetCursorPos(&m_window, &mouseDeltaX, &mouseDeltaY);
    m_mouseDeltaPos.x = (float)mouseDeltaX - (float)m_lastMousePos.x;
    m_mouseDeltaPos.y = (float)mouseDeltaY - (float)m_lastMousePos.y;

    //Update last input data
    double lastMouseDeltaX, lastMouseDeltaY = 0.0f;
    glfwGetCursorPos(&m_window, &lastMouseDeltaX, &lastMouseDeltaY);
    m_lastMousePos.x = lastMouseDeltaX;
    m_lastMousePos.y = lastMouseDeltaY;
}

glm::vec2 InputManager::GetMouseDeltaRaw() const {
    return m_mouseDeltaPos;
}

glm::vec2 InputManager::GetMouseDelta() const {
    return m_mouseDeltaPos * m_time.GetDeltaTime();
}

bool InputManager::UpPressed(){
    if(glfwGetKey(&m_window, GLFW_KEY_Q) == GLFW_PRESS){ 
        return true;
    }
    return false;
}

bool InputManager::DownPressed(){
    if(glfwGetKey(&m_window, GLFW_KEY_E) == GLFW_PRESS){ 
        return true;
    }
    return false;
}

bool InputManager::LeftPressed(){
    if(glfwGetKey(&m_window, GLFW_KEY_A) == GLFW_PRESS){ 
        return true;
    }
    return false;
}

bool InputManager::RightPressed(){
    if(glfwGetKey(&m_window, GLFW_KEY_D) == GLFW_PRESS){ 
        return true;
    }
    return false;
}

bool InputManager::ForwardPressed(){
    if(glfwGetKey(&m_window, GLFW_KEY_W) == GLFW_PRESS){ 
        return true;
    }
    return false;
}

bool InputManager::BackwardsPressed(){
    if(glfwGetKey(&m_window, GLFW_KEY_S) == GLFW_PRESS){ 
        return true;
    }
    return false;
}

bool InputManager::SpeedUpPressed(){
    if(glfwGetKey(&m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        return true;
    }
    return false;
}

bool InputManager::PausePressed() {
    if (glfwGetKey(&m_window, GLFW_KEY_F1) == GLFW_PRESS) {
        if (!pressedEdit) {
            pressedEdit = true;
            return true;
        }
    } else {
        pressedEdit = false; // Reset state when key is released
    }
    return false;
}
