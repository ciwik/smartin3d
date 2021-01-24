#include "Window.h"

using namespace smartin;

int main() {
    graphics::Window* window = new graphics::Window(1280, 720);
    window->Init("Test Window");

    // Main loop
    while (!window->IsAboutToClose()) {
        window->Render();
    }

    return 0;
}
