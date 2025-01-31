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
#include <Material.h>

//Funcs
void applyMatrices(GLFWwindow* window, float currentTime);
void initShaders();
void imguiOptionsWidget();
void imguiEditModeLabel();
void imguiLightsWidget();
void imguiMaterialsWidget();
void imguiShowMessage(float time, const char* message);
void setupObjVertices(std::string modelPath);
void initLights();

//Const values
const glm::vec3 modelPos = glm::vec3(0.0f, -2.0f, 0.0f);
const glm::vec3 cameraStartPos = glm::vec3(0.0f, -2.0f, 7.5f);

//Vars
GLuint mvLoc, projLoc, normLoc;//location of the model-view, projection and normals matrix in the shader
GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, matAmbLoc, matDiffLoc, matSpecLoc, matShineLoc;// Ambient, diffuse, specular params for the vertices and the same for the materials (+ shininess)
glm::mat4 vMatrix, mMatrix, mvMatrix, projMatrix, normMatrix; // normalsMatrix = inverseTransposeMatrix (in terms of calculations)

glm::vec3 currentLightPos, lightPosV; // light position as Vector3, in both model and view space
float lightPos[3]; // light position as float array
glm::vec3 startLightPos = glm::vec3(5.0f, 2.0f, 2.0f);

//White Light properties
float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

//Object Material properties
float* matAmbient = Material::GetDefaultAmbient();
float* matDiffuse = Material::GetDefaultDiffuse();
float* matSpecular = Material::GetDefaultSpecular();
float* matShininess = Material::GetDefaultShininess();

float cameraInputX, cameraInputY;
float aspect;
float cameraBonusSpeed;
int width, height;
float imguiMessageDuration = 2.0f;
float imguiMessageTimer = 0.0f;
bool isInPauseMode = false;
bool showLoadPrimitiveMessage = false;
bool showLoadObjMessage = false;
bool showTextureMessage = false;
bool tiktok = false;

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
#define numVBOs 3 //vertices + textures + normals
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
int numVertices;

void init(GLFWwindow* window) {
    timeManager = new TimeManager();
    bufferManager = new BufferManager();
    imguiManager = new ImguiManager(*window, *timeManager);
    inputManager = new InputManager(*window, *timeManager);
    camera = new Camera(*timeManager, *inputManager);
    modelTexture = new Texture("./resources/textures/PlaceholderTexture.png");

    camera->SetPos(cameraStartPos);
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    projMatrix = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);
    currentLightPos = glm::vec3(startLightPos.x, startLightPos.y, startLightPos.z);

    //adjust Opengl settings and draw model
    glEnable(GL_DEPTH_TEST);//enable depth testing
    glDepthFunc(GL_LEQUAL);

    initShaders();
    initLights();
}

void initShaders()
{
    shaderManager = new ShaderManager();
    vertexShader = new Shader(*shaderManager);
    fragmentShader = new Shader(*shaderManager);

    vertexShader->CreateShader("./resources/shaders/vertexShader.glsl", Shader::ShaderType::Vertex);
    fragmentShader->CreateShader("./resources/shaders/fragmentShader.glsl", Shader::ShaderType::Fragment);

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
    imguiLightsWidget();
    imguiMaterialsWidget();
    applyMatrices(window, (float)currentTime);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);

    //TODO: implement this with event system
    Utils::checkOpenGLError(__FILE__, __LINE__);
}

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

void setupObjVertices(std::string modelPath) {
    OBJModelImporter model;
    model.parseObjFile(modelPath.c_str());
    numVertices = model.getNumVertices();

    std::vector<float> modelVertices = model.getVertices();
    std::vector<float> modelTexCoords = model.getTexCoords();
    std::vector<float> modelNormalCoords = model.getNormals();

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

    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, modelNormalCoords.size() * sizeof(float), &modelNormalCoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);
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
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Mode: %s", isInPauseMode ? "PauseMode \n Press F1 to change to FreeMovementMode" : "FreeMovementMode \n Press F1 to change to PauseMode");

    ImGui::End();
}

void imguiLightsWidget() {
    ImGui::SetNextWindowPos(ImVec2(width - 360.0f, 50.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 0), ImVec2(400, FLT_MAX));

    ImGui::Begin("Lights Menu");
    ImGui::CloseCurrentPopup();

    ImGui::Text("Global Ambient Light");
    if (ImGui::SliderFloat("R##Global", &globalAmbient[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Global", &globalAmbient[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Global", &globalAmbient[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Global", &globalAmbient[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::Text("Ambient Light");
    if (ImGui::SliderFloat("R##Ambient", &lightAmbient[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Ambient", &lightAmbient[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Ambient", &lightAmbient[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Ambient", &lightAmbient[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::Text("Diffuse Light");
    if (ImGui::SliderFloat("R##Diffuse", &lightDiffuse[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Diffuse", &lightDiffuse[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Diffuse", &lightDiffuse[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Diffuse", &lightDiffuse[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::Text("Specular Light");
    if (ImGui::SliderFloat("R##Specular", &lightSpecular[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Specular", &lightSpecular[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Specular", &lightSpecular[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Specular", &lightSpecular[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::End();
}

void imguiMaterialsWidget() {
    ImGui::SetNextWindowPos(ImVec2(width - 360.0f, 120), ImGuiCond_Always);
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 0), ImVec2(400, FLT_MAX));

    ImGui::Begin("Materials Menu");
    ImGui::CloseCurrentPopup();

    ImGui::Text("Material Ambient");
    if (ImGui::SliderFloat("R##Global", &matAmbient[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Global", &matAmbient[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Global", &matAmbient[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Global", &matAmbient[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::Text("Material Diffuse");
    if (ImGui::SliderFloat("R##Ambient", &matDiffuse[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Ambient", &matDiffuse[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Ambient", &matDiffuse[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Ambient", &matDiffuse[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::Text("Material Specular");
    if (ImGui::SliderFloat("R##Diffuse", &matSpecular[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Diffuse", &matSpecular[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Diffuse", &matSpecular[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Diffuse", &matSpecular[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::Text("Material Shininess");
    if (ImGui::SliderFloat("R##Specular", &matShininess[0], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("G##Specular", &matShininess[1], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("B##Specular", &matShininess[2], 0, 1.0f, "%.2f")
        || ImGui::SliderFloat("A##Specular", &matShininess[3], 0, 1.0f, "%.2f")) {
        initLights();
        }
    ImGui::Spacing();

    ImGui::End();
}



void applyMatrices(GLFWwindow* window, float currentTime){
    mvLoc = glGetUniformLocation(shaderManager->GetProgramId(), "mvMatrix");
    projLoc = glGetUniformLocation(shaderManager->GetProgramId(), "projMatrix");
    normLoc = glGetUniformLocation(shaderManager->GetProgramId(), "normMatrix");

    vMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-camera->GetPos().x, -camera->GetPos().y, -camera->GetPos().z));
    mMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(modelPos.x, modelPos.y, modelPos.z));

    //TODO: save the last rotation position before closing this off
    if (!isInPauseMode) {
        mMatrix = glm::rotate(mMatrix, camera->GetRot().x, glm::vec3(0.0f, 1.0f, 0.0f));
        mMatrix = glm::rotate(mMatrix, -camera->GetRot().y, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    mvMatrix = vMatrix * mMatrix;
    normMatrix = glm::transpose(glm::inverse(mvMatrix));

    //Load the program with our shaders to the GPU
    shaderManager->UseShaders();
    
    // send matrix data to the uniform variables
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMatrix));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
    glUniformMatrix4fv(normLoc, 1, GL_FALSE, glm::value_ptr(normMatrix));
}

void initLights() {
    //convert light's position to view space, in a float array
    lightPosV = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0f));
    lightPos[0] = lightPosV.x;
    lightPos[1] = lightPosV.y;
    lightPos[2] = lightPosV.z;

    //Get the light and materials uniforms from the shaders
    globalAmbLoc = glGetUniformLocation(shaderManager->GetProgramId(), "globalAmbient");
    ambLoc = glGetUniformLocation(shaderManager->GetProgramId(), "light.ambient");
    diffLoc = glGetUniformLocation(shaderManager->GetProgramId(), "light.diffuse");
    specLoc = glGetUniformLocation(shaderManager->GetProgramId(), "light.specular");
    posLoc = glGetUniformLocation(shaderManager->GetProgramId(), "light.position");
    matAmbLoc = glGetUniformLocation(shaderManager->GetProgramId(), "material.ambient");
    matDiffLoc = glGetUniformLocation(shaderManager->GetProgramId(), "material.diffuse");
    matSpecLoc = glGetUniformLocation(shaderManager->GetProgramId(), "material.specular");
    matShineLoc = glGetUniformLocation(shaderManager->GetProgramId(), "material.shininess");

    //Set the light and material values in the shaders
    glProgramUniform4fv(shaderManager->GetProgramId(), globalAmbLoc, 1, globalAmbient);
    glProgramUniform4fv(shaderManager->GetProgramId(), ambLoc, 1, lightAmbient);
    glProgramUniform4fv(shaderManager->GetProgramId(), diffLoc, 1, lightDiffuse);
    glProgramUniform4fv(shaderManager->GetProgramId(), specLoc, 1, lightSpecular);
    glProgramUniform4fv(shaderManager->GetProgramId(), posLoc, 1, lightPos);
    glProgramUniform4fv(shaderManager->GetProgramId(), matAmbLoc, 1, matAmbient);
    glProgramUniform4fv(shaderManager->GetProgramId(), matDiffLoc, 1, matDiffuse);
    glProgramUniform4fv(shaderManager->GetProgramId(), matSpecLoc, 1, matSpecular);
    glProgramUniform4fv(shaderManager->GetProgramId(), matShineLoc, 1, matShininess);
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