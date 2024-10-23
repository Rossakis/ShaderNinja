#include <glad/glad.h>//should always be included before glfw
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

#include <Utils.h>

#define numVAOs 1 // VAO = Vertex Array Objects 

GLuint renderingProgram;
GLuint vao[numVAOs]; 
float lastTime = 0.0f;
float deltaTime = 0.0f;

//Initializes the OpenGL pipeline (vertex shader, fragment shader, etc...)
void init(GLFWwindow* window) {
    renderingProgram = Utils::createShaderProgram("../resources/vertexShader.glsl", "../resources/fragmentShader.glsl");
    glPointSize(30.0f);
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

float posX = 0.0f;
float inc = 0.5f;
void moveTriangle(float *x, float *increment){
    *x += *increment * deltaTime;

    if(*x > 1.0f)
        *increment = -(*increment);//move to left
    if(*x < -1.0f)
        *increment = abs(*increment);//move to right

    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLoc, posX);
}


void display(GLFWwindow* window, double currentTime) {
    //Clear buffers for HSR
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //Load the program with our shaders to the GPU
    glUseProgram(renderingProgram);

    moveTriangle(&posX, &inc);

    //Change the vertex shader's x-position field
    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLoc, posX);

    //Initiate pipeline processing
    glDrawArrays(GL_TRIANGLES, 0, 3); 

    //when depth buffer is cleared, it goes to 1 (farthest from the camera)
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

GLFWwindow* setScreenMode(bool isFullScreen) {

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

    //Screen Mode
    GLFWwindow* window = setScreenMode(false);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    //Init Glad and load OpenGL functions through it
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to load OpenGL context\n");
    }

    //Enable V-Sync
    glfwSwapInterval(1);// 1 = number of screen updates before the GLFW buffers get swapped

    init(window);
    
    // std::cout << ShaderStream::shaderToString("fragmentShader.glsl") << std::endl;
    lastTime = glfwGetTime();

    //Wait until user closes the window
    while (!glfwWindowShouldClose(window)) {
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();
        display(window, glfwGetTime());
        processInput(window);//if we processInput after glfwPollEvents, then input will be delayed until the next frame

        glfwSwapBuffers(window);//GLFW windows are double-buffered (meaning there are two color buffers)
        glfwPollEvents();//poll event for input (mouse, keyboard, joystick, etc...)
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}