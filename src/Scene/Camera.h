#pragma once

#include <CommonIncludes.h>
#include <InputManager.h>

class Camera{
    public:
        Camera(TimeManager& time, InputManager& input);
        ~Camera();
        void Update();
        glm::vec3 GetPos();
        void SetPos(glm::vec3 pos);
        glm::vec2 GetRot();

    private:
        float const CAMERA_SPEED_SCALE_X = 5.0f;
        float const CAMERA_SPEED_SCALE_Y = 5.0f;
        float const CAMERA_SPEED_SCALE_Z = 5.0f;
        float const CAMERA_BONUS_SPEED = 5.0f;
        float const MOUSE_SPEED_SCALE_X = 0.25f;
        float const MOUSE_SPEED_SCALE_Y = 0.25f;

        TimeManager& m_time;
        InputManager& m_input;
        glm::vec3 m_position;
        glm::vec2 m_rotation;
        float m_bonusCameraSpeed;

};