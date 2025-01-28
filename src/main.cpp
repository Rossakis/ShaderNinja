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
#include <OBJModelImporter.h>

//Funcs
void applyMatrices(GLFWwindow* window, float currentTime);
void initShaders();
void imguiOptionsWidget();
void imguiEditModeLabel();
void imguiShowMessage(float time, const char* message);
void setupObjVertices();

//Const values
const glm::vec3 modelPos = glm::vec3(0.0f, -2.0f, 0.0f);
const glm::vec3 cameraStartPos = glm::vec3(0.0f, -2.0f, 7.5f);

//Vars
GLint mvLoc, projLoc;//location of the model-view and projection matrix in the shader
glm::mat4 vMat, mMat, mvMat, projMat, trMat; 
float cameraInputX, cameraInputY;
float aspect;
float cameraBonusSpeed;
int width, height;
float imguiMessageDuration = 2.0f;
float imguiMessageTimer = 0.0f;
bool isInPauseMode = false;

//Custom objects
ShaderManager* shaderManager = nullptr;
Shader* vertexShader = nullptr;
Shader* fragmentShader = nullptr; 
BufferManager* bufferManager = nullptr;
Texture* modelTexture = nullptr;
Camera* camera = nullptr;
InputManager* inputManager = nullptr;
TimeManager* timeManager = nullptr;
ImguiManager* imguiManager = nullptr;

#define numVAOs 1
#define numVBOs 2 //vertices + textures
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
int numVertices;

void init(GLFWwindow* window) {
    timeManager = new TimeManager();
    bufferManager = new BufferManager();
    imguiManager = new ImguiManager(*window, *timeManager);
    inputManager = new InputManager(*window, *timeManager);
    camera = new Camera(*timeManager, *inputManager);
    modelTexture = new Texture("../../resources/textures/PlaceholderTexture.png");

    camera->SetPos(cameraStartPos);
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);

    //adjust Opengl settings and draw model
    glEnable(GL_DEPTH_TEST);//enable depth testing
    glDepthFunc(GL_LEQUAL);

    initShaders();
}

void setupObjVertices(std::string modelPath) {
    OBJModelImporter model;
    model.parseObjFile(modelPath.c_str());
    numVertices = model.getNumVertices();

    std::vector<float> modelVertices = model.getVertices();
    auto modelTexCoords = model.getTexCoords();

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(float), &modelVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // Textures
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, modelTexCoords.size() * sizeof(float), &modelTexCoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
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

    imguiOptionsWidget();
    imguiEditModeLabel();
    applyMatrices(window, (float)currentTime);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);

    //TODO: implement this with event system
    Utils::checkOpenGLError(__FILE__, __LINE__);
}

bool showLoadPrimitiveMessage = false;
bool showLoadObjMessage = false;
bool showTextureMessage = false;
bool tiktok = false;

void imguiOptionsWidget() {
    ImGui::Begin("Options");

    //Load Primitive
    if (ImGui::Button("Load Default Cube")) {
        Primitive::CreatePrimitiveCube(bufferManager);
    }

    //Load new OBJ model
    if (ImGui::Button("Load OBJ Model")) {
        imguiManager->OpenFileDialog(OBJ);
    }
    if (imguiManager->GetFileDialog(OBJ)->HasSelected()) {
        setupObjVertices(imguiManager->GetFileDialog(OBJ)->GetSelected().string());
        imguiManager->GetFileDialog(OBJ)->ClearSelected();
        showLoadObjMessage = true;
    }
    imguiManager->printMessage(showLoadObjMessage, imguiMessageDuration, ("Successfully added: \n " + imguiManager->GetFileDialog(OBJ)->GetSelected().string()).c_str());

    //Change Texture
    if (ImGui::Button("Change Texture")) {
        imguiManager->OpenFileDialog(TEXTURE);
    }

    if (imguiManager->GetFileDialog(TEXTURE)->HasSelected()) {
        modelTexture->LoadTexture(imguiManager->GetFileDialog(TEXTURE)->GetSelected().string().c_str());
        imguiManager->GetFileDialog(TEXTURE)->ClearSelected();
        showTextureMessage = true;
    }
    imguiManager->printMessage(showTextureMessage, imguiMessageDuration, ("Successfully changed texture to: \n " + imguiManager->GetFileDialog(TEXTURE)->GetSelected().string()).c_str());

    //Reset Camera Position
    if (ImGui::Button("Reset Camera Pos")) {
        camera->SetPos(cameraStartPos);
    }

    ImGui::End();
}

void imguiEditModeLabel() {
    ImGui::SetNextWindowPos(ImVec2(width / 2.0f, 20.0f), ImGuiCond_Always, ImVec2(0.5f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(350, 50)); // Adjust size if needed

    // Create a transparent, non-interactive window
    ImGui::Begin("PlayMode Indicator", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                 ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoInputs);

    // Set text color
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Mode: %s", isInPauseMode ? "PauseMode" : "FreeMovementMode");

    ImGui::End();
}

void applyMatrices(GLFWwindow* window, float currentTime){    
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->GetPos().x, -camera->GetPos().y, -camera->GetPos().z));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(modelPos.x, modelPos.y, modelPos.z));

    if (!isInPauseMode) {
        mMat = glm::rotate(mMat, camera->GetRot().x, glm::vec3(0.0f, 1.0f, 0.0f));
        mMat = glm::rotate(mMat, -camera->GetRot().y, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    mvMat = vMat * mMat;

    //Load the program with our shaders to the GPU
    shaderManager->UseShaders();
    
    // send matrix data to the uniform variables
    glUniformMatrix4fv(glGetUniformLocation(shaderManager->GetProgramId(), "mvMat"), 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(glGetUniformLocation(shaderManager->GetProgramId(), "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
}

int main() {
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
        glfwPollEvents();//poll event for input (mouse, keyboard, joystick, etc...)
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        imguiManager->UpdateFrame();//should be called before 3D rendering below

        display(window, glfwGetTime());
        timeManager->UpdateTime();
        inputManager->UpdateInput();
        camera->Update();

        imguiManager->UpdateFileDialog();
        imguiManager->Render();

        if (inputManager->PausePressed()) {
            isInPauseMode = !isInPauseMode;
        }

        glfwSwapBuffers(window);//GLFW windows are double-buffered (meaning there are two color buffers)
    }

    imguiManager->Exit();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}