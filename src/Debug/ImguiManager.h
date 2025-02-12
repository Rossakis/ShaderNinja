#pragma once

#include <CommonIncludes.h>
#include <TimeManager.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imfilebrowser.h>

enum DialogFileType {
    OBJ,
    TEXTURE
};

class ImguiManager {
    public:
        ImguiManager(GLFWwindow& window, TimeManager& time);
        ~ImguiManager();
        void UpdateFrame();
        void UpdateFileDialog();
        void Render();
        void Exit();
        void printMessage(bool &messageEnabled, float duration, const char *message);
        void OpenFileDialog(DialogFileType fileType);
        ImGui::FileBrowser* GetFileDialog(DialogFileType fileType);
    private:
        GLFWwindow& m_window;
        TimeManager& m_timeManager;
        ImGui::FileBrowser m_objFileDialog;
        ImGui::FileBrowser m_textureFileDialog;
        float m_messageTimer;
        float m_duration;
        void InitIMGUI();
        void SetFileDialogParameters();
};
