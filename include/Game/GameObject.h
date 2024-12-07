#pragma once

#include <CommonIncludes.h>

class GameObject{
    public:
        GameObject();
        ~GameObject();
    
    private:
        std::stack<glm::mat4> m_transform_stack;
};