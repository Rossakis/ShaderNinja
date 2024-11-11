#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES //make sure types are properly aligned for SIMD operations (e.g. glm's matrix multiplication)

//Dependencies
#include <glad/glad.h>//should always be included before glfw
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Standard libraries
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

//Include headers
#include <Utils.h>
#include <ScreenUtils.h>
#include <InputManager.h>

// #define numVAOs 1
#define numVBOs 2 
#define CAMERA_SPEED_SCALE_X 5.0f;
#define CAMERA_SPEED_SCALE_Y 5.0f;
#define CAMERA_SPEED_SCALE_Z 5.0f;

#define MOUSE_SPEED_SCALE_X 0.25f;
#define MOUSE_SPEED_SCALE_Y 0.25f;

GLuint renderingProgram;
GLint mvLoc, projLoc;//location of the model-view and projection matrix in the shader

GLuint vao[1]; // VAO = Vertex Array Objects 
GLuint vbo[numVBOs]; // VBO = Vertex Buffer Objects 

glm::mat4 vMat, mMat, mvMat, projMat; 
int width, height;
float aspect;

float cameraPosX, cameraPosY, cameraPosZ;
float cameraInputX, cameraInputY;
float cubeLocX, cubeLocY, cubeLocZ;
float deltaTime;
float angle;

void setupVertices(void) {
     // 12 triangles * 3 vertices * 3 values (x, y, z)
    float vertexPositions[108] = {
        -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
    };

    glGenVertexArrays(1, vao);//Create VAOs
    glBindVertexArray(vao[0]);//Make the VAO active

    glGenBuffers(numVBOs, vbo);//Create VBOs
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);//make the "0th" buffer active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);// loads the cube vertices into the 0th VBO buffer
}

void init(GLFWwindow* window) {
    renderingProgram = Utils::createShaderProgram("../resources/shaders/vertexShader.glsl", "../resources/shaders/fragmentShader.glsl");
    cameraPosX = 0.0f; cameraPosY = 0.0f; cameraPosZ = 8.0f;
    cameraInputX = 0.0f, cameraInputY = 0.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
    angle = 0;
    setupVertices();
}

void applyMatrices(GLFWwindow* window){
    // get locations of uniforms in the shader program
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix"); //get locations of the uniforms in the shader program

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPosX, -cameraPosY, -cameraPosZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
    
    mMat = glm::rotate(mMat, cameraInputX, glm::vec3(0.0f, 1.0f, 0.0f));//Y-axis
    mMat = glm::rotate(mMat, -cameraInputY, glm::vec3(1.0f, 0.0f, 0.0f));//X-axis

    mvMat = vMat * mMat;

    // send matrix data to the uniform variables
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
}

void processCameraInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //Left
        cameraPosX -= deltaTime * CAMERA_SPEED_SCALE_X;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //Right
        cameraPosX += deltaTime * CAMERA_SPEED_SCALE_X;
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) //Down
        cameraPosY -= deltaTime * CAMERA_SPEED_SCALE_Y;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) //Up
        cameraPosY += deltaTime * CAMERA_SPEED_SCALE_Y;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //Front
        cameraPosZ -= deltaTime * CAMERA_SPEED_SCALE_Z;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //Back
        cameraPosZ += deltaTime * CAMERA_SPEED_SCALE_Z;
    
    cameraInputX += InputManager::instance().getMouseDelta().x * MOUSE_SPEED_SCALE_X;
    cameraInputY += InputManager::instance().getMouseDelta().y * MOUSE_SPEED_SCALE_Y;
}

void display(GLFWwindow* window, double currentTime) {
    //Clear buffers for HSR
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    //Load the program with our shaders to the GPU
    glUseProgram(renderingProgram);

    applyMatrices(window);
    processCameraInput(window);
    
    //associate VBO with the corresponding vertex attribute in vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // makes the 0th buffer "active"
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);// associates 0th attribute with buffer
    glEnableVertexAttribArray(0);// enable the 0th vertex attribute

    //adjust Opengl settings and draw model
    glEnable(GL_DEPTH_TEST);//enable depth testing
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDrawArrays(GL_TRIANGLES, 0, 36); 
    Utils::checkOpenGLError(__FILE__, __LINE__);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* setScreenMode(bool isFullScreen) {
    if (isFullScreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();//get current main monitor
        const GLFWvidmode* mode = glfwGetVideoMode(monitor); //set full screen
        return glfwCreateWindow(mode->width, mode->height, "Shader Ninja", monitor, NULL);
    }
    else{
        ScreenUtils::setResolutionHD(&width, &height);
        return glfwCreateWindow(width, height, "Shader Ninja", NULL, NULL);
    }
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
    //Wait until user closes the window
    while (!glfwWindowShouldClose(window)) {
        TimeManager::instance().updateTime();
        InputManager::instance().updateInput(window);
        deltaTime = TimeManager::instance().getDeltaTime();

        display(window, glfwGetTime());
        processInput(window);//if we processInput after glfwPollEvents, then input will be delayed until the next frame

        glfwSwapBuffers(window);//GLFW windows are double-buffered (meaning there are two color buffers)
        glfwPollEvents();//poll event for input (mouse, keyboard, joystick, etc...)
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}