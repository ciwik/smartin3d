#include <iostream>
#include "Window.h"
#include "Time.h"
#include "Log.h"

using namespace smartin;

int main() {
    utils::log::Init(std::cout);

    graphics::Window* window = new graphics::Window(1280, 720);
    window->Init("Test Window");

    // Main loop
    while (!window->IsAboutToClose()) {
        utils::time::Update(glfwGetTime());

        window->Render();

        utils::log::I("Time", "FPS = " + std::to_string(1.0f / utils::time::GetDeltaTime()));
    }

    return 0;
}
