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
        void PreRender() const;
        void Render() const;

        inline GLuint GetWidth() const { return width; }
        inline GLuint GetHeight() const { return height; }
        float GetAspectRatio() const;

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