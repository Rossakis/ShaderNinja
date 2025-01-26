#pragma once

#include <CommonIncludes.h>
#include <TimeManager.h>
#include <imgui.h>
#include <imfilebrowser.h>

enum FileBrowserType {
    OBJ,
    TEXTURE
};

class ImguiManager {
    public:
        ImguiManager(TimeManager& time);
        ~ImguiManager();
        void printMessage(bool &messageEnabled, float duration, const char *message);
        void Update();
        const char* OpenFileBrowser(FileBrowserType fileType);
    private:
        TimeManager& m_timeManager;
        ImGui::FileBrowser m_objFileDialog;
        ImGui::FileBrowser m_textureFileDialog;
        float m_messageTimer;
        float m_duration;
};
