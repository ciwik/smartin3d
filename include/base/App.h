#ifndef SMARTIN3D_APP_H
#define SMARTIN3D_APP_H

#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <iostream>
#include <string>
#include <vector>

#include "graphics/Window.h"
#include "base/Job.h"
#include "utils/Input.h"
#include "utils/OpenGLContext.h"
#include "utils/AssetUtils.h"
#include "graphics/Render.h"

namespace smartin::base {
    class App {
    public:
        App(const std::string& name, unsigned int width = DEFAULT_WINDOW_WIDTH, unsigned int height = DEFAULT_WINDOW_HEIGHT);

        void Init();
        void Run();
        void Close();

        inline Camera* GetCamera() const { return mainCamera; }

        void CreateCamera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                          const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f),
                          float fov = 45.0f);
        void SetSkybox(const std::array<std::string, 6>& faceTexturePaths);
        void AddActor(const std::string& name,
                      const std::string& modelFileName,
                      const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                      const glm::vec3& size = glm::vec3 (1.0f, 1.0f, 1.0f),
                      const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));
        void AddJob(Job* job);

        ~App();

    private:
        bool CreateWindow(int width, int height, const std::string& title);

        std::string name;
        unsigned int windowWidth, windowHeight;

        graphics::Window* window;
        std::vector<base::Job*> jobs;
        Camera* mainCamera;

        static const unsigned int DEFAULT_WINDOW_WIDTH = 1280;
        static const unsigned int DEFAULT_WINDOW_HEIGHT = 720;

        const std::string DEFAULT_SHADER_NAME = "default";
        const std::string DEFAULT_SKY_SHADER_NAME = "skybox";
    };
}

#endif //SMARTIN3D_APP_H
