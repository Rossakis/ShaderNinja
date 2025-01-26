
#include "ImguiManager.h"

ImguiManager::ImguiManager(TimeManager &time) : m_timeManager(time){
    m_objFileDialog.SetTitle(".OBJ file Search");
    m_objFileDialog.SetTypeFilters({ ".obj" });

    m_textureFileDialog.SetTitle(".PNG/.JPG file Search");
    m_textureFileDialog.SetTypeFilters({ ".jpg", ".png" });
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

void ImguiManager::Update() {
    m_objFileDialog.Display();
    m_textureFileDialog.Display();

    if(m_objFileDialog.HasSelected())
    {
        std::cout << "Selected filename" << m_objFileDialog.GetSelected().string() << std::endl;
        m_objFileDialog.ClearSelected();
        return;
    }

    if(m_textureFileDialog.HasSelected())
    {
        std::cout << "Selected filename" << m_textureFileDialog.GetSelected().string() << std::endl;
        m_textureFileDialog.ClearSelected();
        return;
    }
}

const char *ImguiManager::OpenFileBrowser(FileBrowserType fileType) {
    if (fileType == OBJ) {
        m_objFileDialog.Open();
    }
    else if (fileType == OBJ) {
        m_textureFileDialog.Open();
    }
}



