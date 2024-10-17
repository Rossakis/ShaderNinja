#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <imgui.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;

    void initWindow()
    {
        //Initialize glfw library
        glfwInit();

        //Define a window that is not OpenGl dependendent
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        //Create the window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Shader Ninja", nullptr, nullptr);
    }
    void initVulkan()
    {

    }

    void mainLoop()
    {
        while(!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}