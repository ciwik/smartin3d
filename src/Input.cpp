#include "Input.h"

void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
void HandleMouse(GLFWwindow* glfwWindow, double x, double y);

void smartin::utils::input::Init(smartin::graphics::Window* window) {
    GLFWwindow* windowInstance = window->GetInstance();

    keyboard::Init(windowInstance);
    mouse::Init(windowInstance);
    gamepad::Init(windowInstance);

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

void smartin::utils::input::keyboard::Init(GLFWwindow* window) {
    glfwSetKeyCallback(window, HandleKeys);
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
    if (lastCursorPosition.x == 0.0f && lastCursorPosition.y == 0.0f) {
        lastCursorPosition = cursorPosition;
    }

    glm::vec2 dPosition = cursorPosition - lastCursorPosition;
    if (smartin::utils::input::mouse::settings::invertYAxis)
        dPosition.y = -dPosition.y;
    deltaCursorPosition = dPosition;

    lastCursorPosition = cursorPosition;
}

void smartin::utils::input::mouse::Init(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, HandleMouse);

    int cursorMode = smartin::utils::input::mouse::settings::showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
    glfwSetInputMode(window, GLFW_CURSOR, cursorMode);
}

void smartin::utils::input::mouse::Update() {
    deltaCursorPosition = glm::vec2(0.0f, 0.0f);
}

glm::vec2 smartin::utils::input::mouse::GetCursorPosition() { return lastCursorPosition; }

glm::vec2 smartin::utils::input::mouse::GetCursorDelta() { return deltaCursorPosition; }


// Gamepad
void smartin::utils::input::gamepad::Init(GLFWwindow* window) { }

void smartin::utils::input::gamepad::Update() { }
