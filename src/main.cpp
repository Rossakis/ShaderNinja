#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define numVAOs 1 // VAO = Vertex Array Objects 

GLuint renderingProgram;
GLuint vao[numVAOs]; 


GLuint createShaderProgram() {

    //STEPS FOR CREATING SHADERS IN OPENGL
    // -------------------------

    // 1) Write Shader Code 
    const GLchar* vertShaderSource =
        "#version 430 core \n"
        "void main(void) \n"
        "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const GLchar* fragShaderSource =
        "#version 430 core \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{ if (gl_FragCoord.x < 635) color = vec4(1.0, 0.0, 0.0, 1.0); else color = vec4(0.0, 0.0, 1.0, 1.0); }";

    // 2) Create Shader Objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 3) Load and Attach Shader Source Code
    glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);

    // 4) Compile the shaders
    glCompileShader(vertexShader);
    glCompileShader(fragShader);

    // 5) Create the ShaderProgram
    GLuint program = glCreateProgram();

    // 6) Attach Shaders abd Link the Shader Program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);//request to the GLSL compiler to ensure that the shaders are compatible  
    
    return program;
}

//Initializes the OpenGL pipeline (vertex shader, fragment shader, etc...)
void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    glPointSize(40.0f);
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
    glUseProgram(renderingProgram);//load the program with our shaders to the GPU
    glDrawArrays(GL_POINTS, 0, 1); //initiate pipeline processing

    //glClearColor(0.0, 0.0, 0.0, 1.0);// Set clear color to black
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear both the color and depth buffer
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

    //Wait until user closes the window
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        processInput(window);//if we processInput after glfwPollEvents, then input will be delayed until the next frame

        glfwSwapBuffers(window);//GLFW windows are double-buffered (meaning there are two color buffers)
        glfwPollEvents();//poll event for input (mouse, keyboard, joystick, etc...)
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}