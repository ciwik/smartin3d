#include "Input.h"

bool smartin::utils::input::IsKeyPressed(GLint keyCode) {
    if (eventHandler != nullptr)
        return eventHandler->IsKeyPressed(keyCode);

    return false;
}

bool smartin::utils::input::IsKeyPressedUp(GLint keyCode) {
    if (eventHandler != nullptr)
        return eventHandler->IsKeyPressedUp(keyCode);

    return false;
}

bool smartin::utils::input::IsKeyPressedDown(GLint keyCode) {
    if (eventHandler != nullptr)
        return eventHandler->IsKeyPressedDown(keyCode);

    return false;
}

void smartin::utils::input::RegisterEventListener(graphics::Window* window) {
    GLFWwindow* windowInstance = window->GetInstance();

    eventHandler = new EventHandler();

    glfwSetKeyCallback(windowInstance, EventHandler::HandleKeys);
    glfwSetCursorPosCallback(windowInstance, EventHandler::HandleMouse);

    // Setup EventHandler object as user of the GLFW window instance
    glfwSetWindowUserPointer(windowInstance, eventHandler);
}

void smartin::utils::input::Update() {
    if (eventHandler != nullptr)
        eventHandler->Update();

    // Get and handle user input events
    glfwPollEvents();
}

glm::vec2 smartin::utils::input::GetMouseDelta() {
    if (eventHandler != nullptr)
        return eventHandler->GetMouseDelta();

    return glm::vec2(0.0f, 0.0f);
}

void smartin::utils::input::EventHandler::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
    if (handler == nullptr)
        return;

    if (action == GLFW_PRESS)
        handler->keysMask.set(key);
    else if (action == GLFW_RELEASE)
        handler->keysMask.reset(key);
}

void smartin::utils::input::EventHandler::HandleMouse(GLFWwindow* glfwWindow, double x, double y) {
    EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(glfwWindow));
    if (handler == nullptr)
        return;

    glm::vec2 cursorPosition = glm::vec2(x, y);

    if (utils::time::GetFrameCount() == 0) {
        // First frame
        handler->lastCursorPosition = cursorPosition;
    }

    glm::vec2 dPosition = cursorPosition - handler->lastCursorPosition;
    if (invertYAxis)
        dPosition.y = -dPosition.y;

    handler->lastCursorPosition = cursorPosition;
}

void smartin::utils::input::EventHandler::Update() {
    prevKeysMask = keysMask;
}

bool smartin::utils::input::EventHandler::IsKeyPressed(int key) {
    return keysMask[key];
}

bool smartin::utils::input::EventHandler::IsKeyPressedDown(int key) {
    return !prevKeysMask[key] && keysMask[key];
}

bool smartin::utils::input::EventHandler::IsKeyPressedUp(int key) {
    return prevKeysMask[key] && !keysMask[key];
}

glm::vec2 smartin::utils::input::EventHandler::GetMouseDelta() {
    return deltaCursorPosition;
}
