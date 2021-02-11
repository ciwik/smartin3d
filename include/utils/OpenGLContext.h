#ifndef SMARTIN3D_OPENGLCONTEXT_H
#define SMARTIN3D_OPENGLCONTEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils/Log.h"

namespace smartin::utils::context {
    static bool InitGLFW() {
        // Init GLFW
        if (!glfwInit()) {
            utils::log::E("OpenGL", "GLFW failed to initialize");
            return false;
        }

        // Setup OpenGL version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        // Core profile = No backward compatibility
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Enable forward compatibility
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        utils::log::I("OpenGL", "GLFW context initialized");
        return true;
    }

    static bool InitGLEW() {
        // Allow modern extension features
        glewExperimental = GL_TRUE;

        // Init GLEW
        if (glewInit() != GLEW_OK) {
            utils::log::E("OpenGL", "GLEW failed to init");
            return false;
        }

        glEnable(GL_DEPTH_TEST);

        utils::log::I("OpenGL", "GLEW context initialized");
        return true;
    }
}

#endif //SMARTIN3D_OPENGLCONTEXT_H
