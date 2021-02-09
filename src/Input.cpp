#include "Input.h"

void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
void HandleMouse(GLFWwindow* glfwWindow, double x, double y);

void smartin::utils::input::RegisterEventListener(smartin::graphics::Window* window) {
    GLFWwindow* windowInstance = window->GetInstance();

    glfwSetKeyCallback(windowInstance, HandleKeys);
    glfwSetCursorPosCallback(windowInstance, HandleMouse);

    // Setup EventHandler object as user of the GLFW window instance
    glfwSetWindowUserPointer(windowInstance, window);
}

void smartin::utils::input::Update() {
    keyboard::Update();
    mouse::Update();
    gamepad::Update();

    // Get and handle user input events
    glfwPollEvents();
}


// Keyboard
std::bitset<KEYS_NUMBER> keysMask;
std::bitset<KEYS_NUMBER> prevKeysMask;

void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    if (glfwGetWindowUserPointer(window) == nullptr)
        return;

    if (action == GLFW_PRESS)
        keysMask.set(key);
    else if (action == GLFW_RELEASE)
        keysMask.reset(key);
}

void smartin::utils::input::keyboard::Update() {
    prevKeysMask = keysMask;
}

bool smartin::utils::input::keyboard::IsKey(int key) { return keysMask[key]; }

bool smartin::utils::input::keyboard::IsKeyUp(int key) { return prevKeysMask[key] && !keysMask[key]; }

bool smartin::utils::input::keyboard::IsKeyDown(int key) { return !prevKeysMask[key] && keysMask[key]; }


// Mouse
glm::vec2 lastCursorPosition;
glm::vec2 deltaCursorPosition;

void HandleMouse(GLFWwindow* window, double x, double y) {
    if (glfwGetWindowUserPointer(window) == nullptr)
        return;

    glm::vec2 cursorPosition = glm::vec2(x, y);

    // If it's first frame
    if (smartin::utils::time::GetFrameCount() == 0) {
        lastCursorPosition = cursorPosition;
    }

    glm::vec2 dPosition = cursorPosition - lastCursorPosition;
    if (smartin::utils::input::mouse::settings::invertYAxis)
        dPosition.y = -dPosition.y;
    deltaCursorPosition = dPosition;

    lastCursorPosition = cursorPosition;
}

void smartin::utils::input::mouse::Update() { }

glm::vec2 smartin::utils::input::mouse::GetCursorPosition() { return lastCursorPosition; }

glm::vec2 smartin::utils::input::mouse::GetCursorDelta() { return deltaCursorPosition; }


// Gamepad
void smartin::utils::input::gamepad::Update() { }
