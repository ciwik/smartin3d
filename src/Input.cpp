#include "Input.h"

void smartin::utils::input::UpdateMouse() {

}

void smartin::utils::input::UpdateKeys() {
    if (eventHandler != nullptr)
        eventHandler->Update();
}

bool smartin::utils::input::IsKeyPressed(GLint keyCode) {
    if (eventHandler != nullptr)
        eventHandler->IsKeyPressed(keyCode);

    return false;
}

bool smartin::utils::input::IsKeyReleased(GLint keyCode) {
    if (eventHandler != nullptr)
        eventHandler->IsKeyReleased(keyCode);

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

void smartin::utils::input::EventHandler::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
    if (handler == nullptr)
        return;

    if (action == GLFW_PRESS)
        handler->keysMask.set(key);
    else if (action == GLFW_RELEASE)
        handler->keysMask.reset(key);
}

void smartin::utils::input::EventHandler::HandleMouse(GLFWwindow *glfwWindow, double x, double y) {

}

void smartin::utils::input::EventHandler::Update() {
    prevKeysMask = keysMask;
}

bool smartin::utils::input::EventHandler::IsKeyPressed(int key) {
    return keysMask[key];
}

bool smartin::utils::input::EventHandler::IsKeyReleased(int key) {
    return prevKeysMask[key] && !keysMask[key];
}
