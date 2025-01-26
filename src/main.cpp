#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES //make sure types are properly aligned for SIMD operations (e.g. glm's matrix multiplication)

#include <Utils.h>
#include <ScreenUtils.h>
#include <InputManager.h>
#include <Texture.h>
#include <Primitive.h>
#include <Camera.h>
#include <BufferManager.h> 
#include <Shader.h>
#include <ImguiManager.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

//Funcs
void init3DModelVertexBuffers();
void applyMatrices(GLFWwindow* window, float currentTime);
void initShaders();
void imguiLoadWidget();
void imguiShowMessage(float time, const char* message);

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
bool createdModel;

bool showMessage;
float imguiMessageDuration = 2.0f;
float imguiMessageTimer = 0.0f;

//Custom objects
ShaderManager* shaderManager = nullptr;
Shader* vertexShader = nullptr;
Shader* fragmentShader = nullptr; 
BufferManager* bufferManager = nullptr;
Texture* cubeTexture = nullptr;
Camera* camera = nullptr;
InputManager* inputManager = nullptr;
TimeManager* timeManager = nullptr;
ImguiManager* imguiManager = nullptr;

void init(GLFWwindow* window) {
    bufferManager = new BufferManager();
    timeManager = new TimeManager();
    inputManager = new InputManager(*window, *timeManager);
    imguiManager = new ImguiManager(*timeManager);
    camera = new Camera(*timeManager, *inputManager);
    cubeTexture = new Texture("../../resources/textures/WallTexture.png");

    camera->SetPos(cameraStartPos);
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);
    createdModel = false;
    showMessage = false;

    //adjust Opengl settings and draw model
    glEnable(GL_DEPTH_TEST);//enable depth testing
    glDepthFunc(GL_LEQUAL);

    //init3DModelVertexBuffers();
    initShaders();
}

void init3DModelVertexBuffers() {
    // std::cout << "Initializing 3D model vertex buffers..." << std::endl;

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

    imguiLoadWidget();
    applyMatrices(window, (float)currentTime);    
    glDrawArrays(GL_TRIANGLES, 0, 36); 

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //TODO: implement this with event system
    Utils::checkOpenGLError(__FILE__, __LINE__);
}

void imguiLoadWidget() {
    // Load Model Obj
    ImGui::Begin("Options");
    if (ImGui::Button("Load OBJ Model")) {
        init3DModelVertexBuffers();
        showMessage = true; // Enable the popup
    }
    imguiManager->printMessage(showMessage, imguiMessageDuration, "Button Pressed Successfully!");
    
    //TODO: Add texture loading
    //char[] pathToTexture;
    ImGui::End();
}

void applyMatrices(GLFWwindow* window, float currentTime){    
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->GetPos().x, -camera->GetPos().y, -camera->GetPos().z));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubePos.x, cubePos.y, cubePos.z));
    mMat = glm::rotate(mMat, camera->GetRot().x, glm::vec3(0.0f, 1.0f, 0.0f));
    mMat = glm::rotate(mMat, -camera->GetRot().y, glm::vec3(1.0f, 0.0f, 0.0f));
    mvMat = vMat * mMat;
    
    //Load the program with our shaders to the GPU
    shaderManager->UseShaders();
    
    // send matrix data to the uniform variables
    glUniformMatrix4fv(glGetUniformLocation(shaderManager->GetProgramId(), "mvMat"), 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(glGetUniformLocation(shaderManager->GetProgramId(), "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
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

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 1.5f;
    ImGui::StyleColorsDark();

    // Initialize imgui backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);// Platform backend
    ImGui_ImplOpenGL3_Init("#version 410");// Renderer backend

    //Update Loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();//poll event for input (mouse, keyboard, joystick, etc...)

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //3D Scene
        display(window, glfwGetTime());
        timeManager->UpdateTime();
        inputManager->UpdateInput();
        camera->Update();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);//GLFW windows are double-buffered (meaning there are two color buffers)
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}