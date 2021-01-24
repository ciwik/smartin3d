#include "Window.h"

smartin::graphics::Window::Window(GLuint _width, GLuint _height) {
    width = _width;
    height = _height;
}

void smartin::graphics::Window::Init(std::string title) {
    // Init GLFW
    if (!glfwInit()) {
        utils::log::E("OpenGL", "GLFW failed to initialize");
        Destroy();
        return;
    }

    // Setup OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Core profile = No backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Enable forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    // Init GLEW
    if (glewInit() != GLEW_OK) {
        utils::log::E("OpenGL", "GLEW failed to init");
        Destroy();
        return;
    }

    glEnable(GL_DEPTH_TEST);

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

void smartin::graphics::Window::Destroy() {
    if (instance != nullptr)
        glfwDestroyWindow(instance);
    glfwTerminate();
}

smartin::graphics::Window::~Window() {
    Destroy();
}
