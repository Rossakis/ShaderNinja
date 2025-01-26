
#include "ImguiManager.h"

ImguiManager::ImguiManager(TimeManager &time) : m_timeManager(time){
    //m_messageEnabled = true;
}

void ImguiManager::printMessage(bool &messageEnabled, float duration, const char *message) {
    if (messageEnabled == true) {
        m_duration = duration;
        m_messageTimer += m_timeManager.GetDeltaTime();

        if (m_messageTimer < m_duration) {
            ImGui::SetNextWindowSize(ImVec2(400, 100)); // Set size for the popup
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.2f) , 0, ImVec2(0.5f, 0.5f)); // Center the popup
            ImGui::Begin("Popup Message", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            ImGui::Text(message);
            ImGui::End();
        } else {
            m_messageTimer = 0.0f;
            messageEnabled = false; // Disable popup after duration
        }
    }
}

