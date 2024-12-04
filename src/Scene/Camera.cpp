#include <Camera.h>

Camera::Camera(TimeManager& time, InputManager& input) : m_time (time), m_input(input) {
    m_position = glm::vec3(0);
    m_rotation = glm::vec2(0);
    m_bonusCameraSpeed = 0.0f;
}

void Camera::UpdatePos(){
    if(m_input.SpeedUpPressed()){
        m_bonusCameraSpeed = CAMERA_BONUS_SPEED;
    }
    else
        m_bonusCameraSpeed = 1;

    if(m_input.LeftPressed()) 
        m_position.x -= m_time.GetDeltaTime() * m_bonusCameraSpeed * CAMERA_SPEED_SCALE_X;

    if(m_input.RightPressed()) 
        m_position.x += m_time.GetDeltaTime() * m_bonusCameraSpeed * CAMERA_SPEED_SCALE_X;

    if(m_input.UpPressed()) 
        m_position.y += m_time.GetDeltaTime() * m_bonusCameraSpeed* CAMERA_SPEED_SCALE_Y;

    if(m_input.DownPressed()) 
        m_position.y -= m_time.GetDeltaTime() * m_bonusCameraSpeed* CAMERA_SPEED_SCALE_Y;

    if(m_input.SpeedUpPressed()) 
        m_position.y += m_time.GetDeltaTime() * m_bonusCameraSpeed* CAMERA_SPEED_SCALE_Y;
        
    if(m_input.ForwardPressed()) 
        m_position.z -= m_time.GetDeltaTime() * m_bonusCameraSpeed* CAMERA_SPEED_SCALE_Z;

    if(m_input.BackwardsPressed()) 
        m_position.z += m_time.GetDeltaTime() * m_bonusCameraSpeed* CAMERA_SPEED_SCALE_Z;

}

void Camera::UpdateRot(){
    m_rotation.x += m_input.GetMouseDelta().x * MOUSE_SPEED_SCALE_X;
    m_rotation.y -= m_input.GetMouseDelta().y * MOUSE_SPEED_SCALE_Y;
}

glm::vec3 Camera::GetPos(){
    return m_position;
}

void Camera::SetPos(glm::vec3 pos){
    m_position = pos;
}

glm::vec2 Camera::GetRot(){
    return m_rotation;
}