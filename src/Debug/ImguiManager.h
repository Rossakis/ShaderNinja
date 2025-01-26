#pragma once

#include <CommonIncludes.h>
#include <TimeManager.h>
#include <imgui.h>

class ImguiManager {
    public:
        ImguiManager(TimeManager& time);
        ~ImguiManager();
        //void Update();
        void printMessage(bool &messageEnabled, float duration, const char *message);
    private:
        TimeManager& m_timeManager;
        float m_messageTimer;
        //bool m_messageEnabled;
        float m_duration;
};
