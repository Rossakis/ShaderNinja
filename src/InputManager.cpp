#include <InputManager.h>

InputManager::InputManager() : mouseDeltaPos (0.0f), lastMousePos(0.0f) {}

void InputManager::updateInput(GLFWwindow *window) {
    
    //Calculate input difference
    double mouseDeltaX, mouseDeltaY = 0.0f;
    glfwGetCursorPos(window, &mouseDeltaX, &mouseDeltaY);
    mouseDeltaPos.x = (float)mouseDeltaX - (float)lastMousePos.x;
    mouseDeltaPos.y = (float)mouseDeltaY - (float)lastMousePos.y;

    //Update last input data
    double lastMouseDeltaX, lastMouseDeltaY = 0.0f;
    glfwGetCursorPos(window, &lastMouseDeltaX, &lastMouseDeltaY);
    lastMousePos.x = lastMouseDeltaX;
    lastMousePos.y = lastMouseDeltaY;
}

glm::vec2 InputManager::getMouseDeltaRaw() const {
    return mouseDeltaPos;
}

glm::vec2 InputManager::getMouseDelta() const {
    return mouseDeltaPos * TimeManager::instance().getDeltaTime();
}