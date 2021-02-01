#ifndef SMARTIN3D_WINDOW_H
#define SMARTIN3D_WINDOW_H

#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Log.h"

namespace smartin::graphics {
    class Window {
    public:
        Window(GLuint width, GLuint height);

        void Instantiate(std::string title);
        void Init();
        void Render();

        bool IsAboutToClose() const;

        ~Window();

    private:
        void Destroy();

        GLFWwindow* instance;

        GLuint width, height;
        GLint bufferWidth, bufferHeight;
    };
}
#endif //SMARTIN3D_WINDOW_H