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
};
