#include "graphics/Window.h"

smartin::graphics::Window::Window(unsigned int _width, unsigned int _height) :
    width(_width),
    height(_height) { }

float smartin::graphics::Window::GetAspectRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}

void smartin::graphics::Window::Instantiate(const std::string& title) {
    instance = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (instance == nullptr) {
        Destroy();
        throw utils::error::OpenGLException("GLFW failed to create window");
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

void smartin::graphics::Window::PreRender() const {
    // Clear the window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void smartin::graphics::Window::Render() const {
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
