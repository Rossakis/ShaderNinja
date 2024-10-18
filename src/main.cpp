#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glad/gl.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define numVAOs 1 //number of vertices

GLuint renderingProgram;
GLuint vertexBuffer[numVAOs];

//Initializes the OpenGL pipeline (vertex shader, fragment shader, etc...)
void init(GLFWwindow* window) {

}

void display(GLFWwindow* window, double currentTime) {
    glClearColor(0.0, 0.0, 0.0, 1.0);// Set clear color to black
    glClear(GL_COLOR_BUFFER_BIT);// Set "clear" color to black
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear both the color and depth buffer
    //when depth buffer is cleared, it goes to 1 (farthest from the camera)
}

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

GLFWwindow* SetScreenMode(bool isFullScreen) {

    if (isFullScreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();//get current main monitor
        const GLFWvidmode* mode = glfwGetVideoMode(monitor); //set full screen
        return glfwCreateWindow(mode->width, mode->height, "Shader Ninja", monitor, NULL);
    }
    return glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shader Ninja", NULL, NULL);
}

int main() {

    //Initialize the GLFW library
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = SetScreenMode(false);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    //Init Glad and Load OpenGL loader through it
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::runtime_error("Failed to load OpenGL context\n");
    }

    //Enable V-Sync
    glfwSwapInterval(1);// 1 = number of screen updates before the GLFW buffers get swapped

    init(window);

    //Wait until user closes the window
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);//GLFW windows are double-buffered (meaning there are two color buffers)
        glfwPollEvents();//poll event for input (mouse, keyboard, joystick, etc...)
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}