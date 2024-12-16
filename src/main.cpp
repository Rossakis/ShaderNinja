#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES //make sure types are properly aligned for SIMD operations (e.g. glm's matrix multiplication)

#include <Utils.h>
#include <ScreenUtils.h>
#include <InputManager.h>
#include <Texture.h>
#include <Primitive.h>
#include <Camera.h>
#include <BufferManager.h> 
#include <Shader.h>

//Funcs
void initVertexBuffers();
void applyMatrices(GLFWwindow* window, float currentTime);
void initShaders();

//Const values
const glm::vec3 cubePos = glm::vec3(0.0f, -2.0f, 0.0f);
const glm::vec3 cameraStartPos = glm::vec3(0.0f, -2.0f, 7.5f);

//Vars
GLint mvLoc, projLoc;//location of the model-view and projection matrix in the shader
glm::mat4 vMat, mMat, mvMat, projMat, trMat; 
float cameraInputX, cameraInputY;
float aspect;
float cameraBonusSpeed;
int width, height;

//Custom objects
ShaderManager* shaderManager = nullptr;
Shader* vertexShader = nullptr;
Shader* fragmentShader = nullptr; 
BufferManager* bufferManager = nullptr;
Texture* cubeTexture = nullptr;
Camera* camera = nullptr;
InputManager* inputManager = nullptr;
TimeManager* timeManager = nullptr;

void init(GLFWwindow* window) {
    bufferManager = new BufferManager();
    timeManager = new TimeManager();
    inputManager = new InputManager(*window, *timeManager);
    camera = new Camera(*timeManager, *inputManager);
    cubeTexture = new Texture("../../resources/textures/Brick-Wall.jpg");

    camera->SetPos(cameraStartPos);
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);

    initVertexBuffers();
    initShaders();

    //adjust Opengl settings and draw model
    glEnable(GL_DEPTH_TEST);//enable depth testing
    glDepthFunc(GL_LEQUAL);
}

void initVertexBuffers(void) {    
    //TODO: make this work with Mesh->GetVerticesSize()
    size_t vertexCount = sizeof(Primitive::CUBE_VERTICES) / sizeof(Primitive::CUBE_VERTICES[0]);
    size_t textureCount = sizeof(Primitive::CUBE_TEXTURE_VERTICES) / sizeof(Primitive::CUBE_TEXTURE_VERTICES[0]); 

    bufferManager->BindVertexBuffer(Primitive::CUBE_VERTICES, vertexCount, BufferManager::BufferType::Vertex);//layout = 0
    bufferManager->BindVertexBuffer(Primitive::CUBE_TEXTURE_VERTICES, textureCount,  BufferManager::BufferType::Texture);//layout = 1
}

void initShaders()
{
    shaderManager = new ShaderManager();
    vertexShader = new Shader(*shaderManager);
    fragmentShader = new Shader(*shaderManager);

    vertexShader->CreateShader("../../resources/shaders/vertexShader.glsl", Shader::ShaderType::Vertex);
    fragmentShader->CreateShader("../../resources/shaders/fragmentShader.glsl", Shader::ShaderType::Fragment);

    shaderManager->AddShader(vertexShader);
    shaderManager->AddShader(fragmentShader);

    shaderManager->LinkShaders();
    shaderManager->UseShaders();
}

void display(GLFWwindow* window, double currentTime) {
    //Clear buffers for HSR
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    applyMatrices(window, (float)currentTime);    
    glDrawArrays(GL_TRIANGLES, 0, 36); 
    
    //TODO: implement this with event system
    Utils::checkOpenGLError(__FILE__, __LINE__);
}

void applyMatrices(GLFWwindow* window, float currentTime){    
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->GetPos().x, -camera->GetPos().y, -camera->GetPos().z));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubePos.x, cubePos.y, cubePos.z));
    mMat = glm::rotate(mMat, camera->GetRot().x, glm::vec3(0.0f, 1.0f, 0.0f));//Y-axis
    mMat = glm::rotate(mMat, -camera->GetRot().y, glm::vec3(1.0f, 0.0f, 0.0f));//X-axis
    mvMat = vMat * mMat;
    
    //Load the program with our shaders to the GPU
    shaderManager->UseShaders();
    
    // send matrix data to the uniform variables
    glUniformMatrix4fv(glGetUniformLocation(shaderManager->GetProgramId(), "mvMat"), 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(glGetUniformLocation(shaderManager->GetProgramId(), "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
    glUniformMatrix4fv(glGetUniformLocation(shaderManager->GetProgramId(), "tc"), 1, GL_FALSE, glm::value_ptr(mvMat));
}

int main() {
    //Initialize the GLFW library
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    GLFWwindow* window = ScreenUtils::setScreenMode(false, width, height);

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

    //Start
    init(window);

    //Update Loop
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