#ifndef SMARTIN3D_OPENGLCONTEXT_H
#define SMARTIN3D_OPENGLCONTEXT_H

#include "precompiled.h"

#include "utils/Log.h"

namespace smartin::utils::context {
    static void InitGLFW() {
        // Init GLFW
        if (!glfwInit())
            throw error::OpenGLException("GLFW failed to initialize");

        // Setup OpenGL version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        // Core profile = No backward compatibility
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Enable forward compatibility
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        utils::log::I("OpenGL", "GLFW context initialized");
    }

    static void InitGLEW() {
        // Allow modern extension features
        glewExperimental = GL_TRUE;

        // Init GLEW
        if (glewInit() != GLEW_OK)
            throw error::OpenGLException("GLEW failed to initialize");

        glEnable(GL_DEPTH_TEST);

        utils::log::I("OpenGL", "GLEW context initialized");
    }
}

#endif //SMARTIN3D_OPENGLCONTEXT_H
