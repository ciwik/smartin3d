#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <iostream>
#include <vector>

#include "OpenGLContext.h"
#include "Window.h"
#include "TimeUtils.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"

using namespace smartin;

// Variables
graphics::Window* window;
std::vector<graphics::Mesh*> meshes;
graphics::Shader* mainShader;
base::Camera* mainCamera;

// Awake methods
void CreateScene();
void RenderScene();
graphics::Window* CreateWindow(int width, int height, const char* title);
base::Camera* CreateCamera(float fov, float aspect, glm::vec3 pos = glm::vec3()) ;
graphics::Shader* CreateShader(const char *vertexCodePath, const char *fragmentCodePath);

// Update methods
void HandleInput();
void UpdateShader(glm::mat4 view, glm::mat4 proj);
void Render();

// Destroy methods
void Exit();


int main() {
    utils::log::Init(std::cout);

    utils::input::mouse::settings::invertYAxis = true;

    window = CreateWindow(1280, 720, "Test window");
    mainShader = CreateShader("shaders/default.vshader", "shaders/default.fshader");
    mainCamera = CreateCamera(60.0f, window->GetWidth() / (float) window->GetHeight());

    CreateScene();

    // Main loop
    while (!window->IsAboutToClose()) {
        utils::time::Update();
        HandleInput();

        mainCamera->Update();
        UpdateShader(mainCamera->GetViewMatrix(), mainCamera->GetProjectionMatrix());
        Render();
    }

    Exit();

    return 0;
}

void CreateScene() {
    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            // X     Y     Z		 U	   V		 Xn	   Yn	 Zn
            -1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
            0.0f, -1.0f,  1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
            0.0f,  1.0f,  0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f,
    };

    graphics::Mesh* mesh = new graphics::Mesh();
    mesh->Init(vertices, indices, 32, 12);
    meshes.push_back(mesh);
}

void RenderScene() {
    for (auto mesh : meshes)
        mesh->Render();
}

graphics::Window* CreateWindow(int width, int height, const char* title) {
    utils::context::InitGLFW();

    graphics::Window* window = new graphics::Window(width, height);
    window->Instantiate(title);

    utils::context::InitGLEW();
    window->Init();

    utils::input::RegisterEventListener(window);

    return window;
}

void HandleInput() {
    utils::input::Update();
    if (utils::input::keyboard::IsKeyUp(KEY_ESCAPE))
        window->Close();

    if (utils::input::keyboard::IsKeyDown(KEY_A))
        utils::log::I("Input", "Pressed key A on frame " + std::to_string(utils::time::GetFrameCount()));
    if (utils::input::keyboard::IsKeyUp(KEY_A))
        utils::log::I("Input", "Released key A on frame " + std::to_string(utils::time::GetFrameCount()));

    glm::vec2 cursorDelta = utils::input::mouse::GetCursorDelta();
}


base::Camera* CreateCamera(float fov, float aspect, glm::vec3 pos) {
    base::Camera* camera = new base::Camera();
    camera->aspect = aspect;
    camera->fieldOfView = fov;
    camera->GetTransform()->Move(pos);

    return camera;
}

graphics::Shader* CreateShader(const char *vertexCodePath, const char *fragmentCodePath) {
    graphics::Shader* shader = graphics::ReadShaderFromFiles(vertexCodePath, fragmentCodePath);
    shader->Compile();
    shader->Validate();

    return shader;
}

void UpdateShader(glm::mat4 view, glm::mat4 proj) {
    mainShader->SetMatrix("view", view);
    mainShader->SetMatrix("projection", proj);
    mainShader->Apply();
}

void Render() {
    RenderScene();
    window->Render();
}

void Exit() {
    // TODO
}