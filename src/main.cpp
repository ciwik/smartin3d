#include <iostream>
#include <vector>

#include "OpenGLContext.h"
#include "Window.h"
#include "STime.h"
#include "Mesh.h"
#include "Shader.h"

using namespace smartin;

graphics::Window* window;

std::vector<graphics::Mesh*> meshes;
void CreateScene();
void RenderScene();

void Exit();

int main() {
    utils::log::Init(std::cout);

    utils::context::InitGLFW();

    graphics::Window* window = new graphics::Window(1280, 720);
    window->Instantiate("Test Window");

    utils::context::InitGLEW();
    window->Init();

    graphics::Shader* mainShader = graphics::ReadShaderFromFiles("shaders/default.vshader", "shaders/default.fshader");
    mainShader->Compile();

    CreateScene();

    // Main loop
    while (!window->IsAboutToClose()) {
        utils::time::Update(glfwGetTime());

        mainShader->Validate();
        mainShader->Apply();

        RenderScene();

        window->Render();

        utils::log::I("Time", "FPS = " + std::to_string(1.0f / utils::time::GetDeltaTime()));
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

void Exit() {
    delete window;
    for (auto mesh : meshes)
        delete mesh;
}