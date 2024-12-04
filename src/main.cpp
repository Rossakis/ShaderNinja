#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES //make sure types are properly aligned for SIMD operations (e.g. glm's matrix multiplication)

#include <CommonIncludes.h>
#include <Utils.h>
#include <ScreenUtils.h>
#include <InputManager.h>
#include <Texture.h>
#include <Primitive.h>
#include <Camera.h>

#define numVBOs 2 

GLuint renderingProgram;
GLint mvLoc, projLoc;//location of the model-view and projection matrix in the shader

GLuint vao[1]; // VAO = Vertex Array Objects
GLuint vbo[numVBOs]; // VBO = Vertex Buffer Objects 

glm::mat4 vMat, mMat, mvMat, projMat, trMat; 
int width, height;
float aspect;

//float cameraPosX, cameraPosY, cameraPosZ;
float cameraInputX, cameraInputY;
glm::vec3 cubeLoc;
float angle;
float cameraBonusSpeed;

//Game objects
Texture* cubeTexture;
Camera* camera;
InputManager* inputManager;
TimeManager* timeManager;

void setupVertices(void) {    
    glGenVertexArrays(1, vao);//Create VAOs
    glBindVertexArray(vao[0]);//Make the VAO active
    glGenBuffers(numVBOs, vbo);//Create VBOs

    //Cube
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);//make the "0th" buffer active
    glBufferData(GL_ARRAY_BUFFER, sizeof(Primitive::CUBE_VERTICES), Primitive::CUBE_VERTICES, GL_STATIC_DRAW);// loads the cube vertices into the 0th VBO buffer

    //Cube-Texture
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Primitive::CUBE_TEXTURE_VERTICES), Primitive::CUBE_TEXTURE_VERTICES, GL_STATIC_DRAW);
    
    //Pyramid
    // glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(Primitive::PYRAMID_VERTICES), Primitive::PYRAMID_VERTICES, GL_STATIC_DRAW);
}

void init(GLFWwindow* window) {
    timeManager = new TimeManager();
    inputManager = new InputManager(*window, *timeManager);
    camera = new Camera(*timeManager, *inputManager);
    camera->SetPos(glm::vec3(0.0f, -2.0f, 7.5f));

    renderingProgram = Utils::createShaderProgram("../resources/shaders/vertexShader.glsl", "../resources/shaders/fragmentShader.glsl");
    cubeTexture = new Texture("../resources/textures/Brick-Wall.jpg");
    
    cubeLoc = glm::vec3(0.0f, -2.0f, 0.0f);
    angle = 0;

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);

    setupVertices();
}

void applyMatrices(GLFWwindow* window, float currentTime){    
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->GetPos().x, -camera->GetPos().y, -camera->GetPos().z));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLoc.x, cubeLoc.y, cubeLoc.z));
    mMat = glm::rotate(mMat, camera->GetRot().x, glm::vec3(0.0f, 1.0f, 0.0f));//Y-axis
    mMat = glm::rotate(mMat, -camera->GetRot().y, glm::vec3(1.0f, 0.0f, 0.0f));//X-axis
    mvMat = vMat * mMat;

    // send matrix data to the uniform variables
    glUniform1f(glGetUniformLocation(renderingProgram, "timeF"), currentTime);
    glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "mvMat"), 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(glGetUniformLocation(renderingProgram, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
}

void display(GLFWwindow* window, double currentTime) {
    //Clear buffers for HSR
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    //Load the program with our shaders to the GPU
    glUseProgram(renderingProgram);
    applyMatrices(window, (float)currentTime);
    
    //Cube 
    //associate VBO with the corresponding vertex attribute in vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // makes the 0th buffer "active"
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);// associates 0th attribute with buffer
    glEnableVertexAttribArray(0);// enable the 0th vertex attribute

    //Texture
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cubeTexture->GetTextureId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //adjust Opengl settings and draw model
    glEnable(GL_DEPTH_TEST);//enable depth testing
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36); 
    
    //TODO: implement this with event system
    Utils::checkOpenGLError(__FILE__, __LINE__);
}

GLFWwindow* setScreenMode(bool isFullScreen) {
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

int main() {
    //Initialize the GLFW library
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

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
        timeManager->UpdateTime();
        inputManager->UpdateInput();
        camera->UpdatePos();
        camera->UpdateRot();
        display(window, glfwGetTime());

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);//GLFW windows are double-buffered (meaning there are two color buffers)
        glfwPollEvents();//poll event for input (mouse, keyboard, joystick, etc...)
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}