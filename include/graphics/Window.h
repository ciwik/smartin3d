#ifndef SMARTIN3D_WINDOW_H
#define SMARTIN3D_WINDOW_H

#include "precompiled.h"

#include "utils/Log.h"

namespace smartin::graphics {
    class Window final {
    public:
        Window(GLuint width, GLuint height);

        bool Instantiate(const std::string& title);
        void Init();
        void PreRender();
        void Render();

        inline GLuint GetWidth() const { return width; }
        inline GLuint GetHeight() const { return height; }
        inline float GetAspectRatio() const { return width / (float)height; }

        inline GLFWwindow* GetInstance() const { return instance; }

        void Close();
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