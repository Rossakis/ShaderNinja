
#include "ImguiManager.h"

ImguiManager::ImguiManager(GLFWwindow& window, TimeManager& time) : m_window(window) ,m_timeManager(time){
    InitIMGUI();
    SetFileDialogParameters();
}

void ImguiManager::InitIMGUI() {
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 1.5f;
    ImGui::StyleColorsDark();

    // Initialize imgui backends
    ImGui_ImplGlfw_InitForOpenGL(&m_window, true);// Platform backend
    ImGui_ImplOpenGL3_Init("#version 410");// Renderer backend
}


void ImguiManager::SetFileDialogParameters() {
    m_objFileDialog.SetTitle(".OBJ file Search");
    m_objFileDialog.SetTypeFilters({ ".obj" });

    m_textureFileDialog.SetTitle(".PNG/.JPG file Search");
    m_textureFileDialog.SetTypeFilters({ ".jpg", ".png" });
}

void ImguiManager::UpdateFrame() {
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiManager::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::Exit() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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

void ImguiManager::UpdateFileDialog() {
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
    }
}

void ImguiManager::OpenFileDialog(DialogFileType fileType) {
    if (fileType == OBJ) {
        m_objFileDialog.Open();
    }
    else if (fileType == TEXTURE) {
        m_textureFileDialog.Open();
    }
}

const char *ImguiManager::GetOpenFileName(DialogFileType fileType) {
    if (fileType == OBJ) {
        if (m_objFileDialog.IsOpened() && m_objFileDialog.HasSelected()) {
            return m_objFileDialog.GetSelected().string().c_str();
        }
    }
    else if (fileType == TEXTURE) {
        if (m_textureFileDialog.IsOpened() && m_textureFileDialog.HasSelected()) {
            return m_textureFileDialog.GetSelected().string().c_str();
        }
    }
    else
        return nullptr;

    //m_textureFileDialog.
}




