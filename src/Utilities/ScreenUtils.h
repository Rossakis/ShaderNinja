#pragma once

class ScreenUtils{
    public:
        static const int HD_SCREEN_WIDTH = 1280;
        static const int HD_SCREEN_HEIGHT = 720;
        static void setResolutionHD(int* width, int* height){
            *width = HD_SCREEN_WIDTH;
            *height = HD_SCREEN_HEIGHT;
        }

        static const int FHD_SCREEN_WIDTH = 1920;
        static const int FHD_SCREEN_HEIGHT = 1080;
        static void setResolutionFHD(int* width, int* height){
            *width = FHD_SCREEN_WIDTH;
            *height = FHD_SCREEN_HEIGHT;
        }

        static GLFWwindow* setScreenMode(bool isFullScreen, int width, int height){
            if (isFullScreen) {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();//get current main monitor
                const GLFWvidmode* mode = glfwGetVideoMode(monitor); //set full screen
                return glfwCreateWindow(mode->width, mode->height, "Shader Ninja", monitor, NULL);
            }
            else{
                ScreenUtils::setResolutionFHD(&width, &height);
                return glfwCreateWindow(width, height, "Shader Ninja", NULL, NULL);
            }
        }
};
