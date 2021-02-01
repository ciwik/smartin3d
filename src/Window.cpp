#include "Window.h"

smartin::graphics::Window::Window(GLuint _width, GLuint _height) {
    width = _width;
    height = _height;
}

void smartin::graphics::Window::Instantiate(std::string title) {
    instance = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (instance == nullptr) {
        utils::log::E("OpenGL", "GLFW failed to create window");
        Destroy();
        return;
    }

    // Get buffer size info
    glfwGetFramebufferSize(instance, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(instance);

    utils::log::I("OpenGL", "Window instantiated");
}

void smartin::graphics::Window::Init() {
    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    utils::log::I("OpenGL", "Window initialized");
}

void smartin::graphics::Window::Render() {
    glfwSwapBuffers(instance);
}

bool smartin::graphics::Window::IsAboutToClose() const {
    return glfwWindowShouldClose(instance);
}

void smartin::graphics::Window::Close() {
    glfwSetWindowShouldClose(instance, GL_TRUE);
}

void smartin::graphics::Window::Destroy() {
    if (instance != nullptr)
        glfwDestroyWindow(instance);
    glfwTerminate();
}

smartin::graphics::Window::~Window() {
    Destroy();
}
