#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <iostream>
#include <vector>

#include "OpenGLContext.h"
#include "Window.h"
#include "STime.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"

using namespace smartin;

graphics::Window* window;

std::vector<graphics::Mesh*> meshes;
void CreateScene();
void RenderScene();

graphics::Window* CreateWindow(int width, int height, const char* title);

void Exit();

int main() {
    utils::log::Init(std::cout);

    window = CreateWindow(1280, 720, "Test window");

    graphics::Shader* mainShader = graphics::ReadShaderFromFiles("shaders/default.vshader", "shaders/default.fshader");
    mainShader->Compile();
    mainShader->Validate();

    base::Camera* camera = new base::Camera();
    camera->aspect = window->GetWidth() / (float) window->GetHeight();

    CreateScene();

    // Main loop
    while (!window->IsAboutToClose()) {
        utils::time::Update(glfwGetTime());

        utils::input::Update();
        if (utils::input::IsKeyPressedUp(KEY_ESCAPE))
            window->Close();

        if (utils::input::IsKeyPressedDown(KEY_A))
            utils::log::I("Input", "Pressed key A");
        if (utils::input::IsKeyPressedUp(KEY_A))
            utils::log::I("Input", "Released key A");

        camera->Update();
        glm::mat4 projection = camera->GetProjectionMatrix();
        glm::mat4 view = camera->GetViewMatrix();

        mainShader->SetMatrix("view", view);
        mainShader->SetMatrix("projection", projection);
        mainShader->Apply();

        RenderScene();

        window->Render();

        //utils::log::I("Time", "FPS = " + std::to_string(1.0f / utils::time::GetDeltaTime()));
    }

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
