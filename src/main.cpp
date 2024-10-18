#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define numVAOs 1 //number of vertices

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() {

    //Define the shaders
    const GLchar* vertShaderSource =
        "#version 430 core \n"
        "void main(void) \n"
        "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const GLchar* fragShaderSource =
        "#version 430 core \n"
        "void main(void) \n"
        "{color = vec4(0.0, 0.0, 1.0, 1.0); }";

    //Create shader instances
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Define the shader sources
    glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);

    //Compile the shaders
    glCompileShader(vertexShader);
    glCompileShader(fragShader);

    //Init the program
    GLuint program = glCreateProgram();

    //Attach shaders to it
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);

    //Link the program and return it
    glLinkProgram(program);
    return program;
}

//Initializes the OpenGL pipeline (vertex shader, fragment shader, etc...)
void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime) {
    glUseProgram(renderingProgram);
    glDrawArrays(GL_POINTS, 0, 1);

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

    //Init Glad and Load OpenGL functions through it
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