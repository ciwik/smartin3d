#ifndef SMARTIN3D_APP_H
#define SMARTIN3D_APP_H

#pragma comment(lib, "legacy_stdio_definitions.lib")

#include "precompiled.h"

#include "graphics/Window.h"
#include "base/Job.h"
#include "utils/Input.h"
#include "utils/OpenGLContext.h"
#include "utils/AssetUtils.h"
#include "utils/Exceptions.h"
#include "graphics/Render.h"

namespace smartin::base {
    class App final {
    public:
        App(const std::string& name, unsigned int width = defaultWindowWidth, unsigned int height = defaultWindowHeight);

        void Init();
        void Run();
        void Close();

        inline std::shared_ptr<Camera> GetCamera() const { return mainCamera; }

        void CreateCamera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                          const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f),
                          float fov = 45.0f);

        void SetSkybox(const std::array<std::string, 6>& faceTexturePaths);

        void AddActor(const std::string& name,
                      const std::string& modelFileName,
                      const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                      const glm::vec3& size = glm::vec3 (1.0f, 1.0f, 1.0f),
                      const glm::vec3& eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));

        void AddDirectionalLight(const std::string& name,
                                 glm::vec3 direction,
                                 bool main = false,
                                 glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
                                 float ambientIntensity = 0.5f,
                                 float diffuseIntensity = 0.5f);

        void SetTargetFPS(unsigned int fps);

        template<class TJob, typename... Args>
        void AddJob(Args... args) {
            static_assert(std::is_base_of<Job, TJob>::value, "Job should be derived from base::Job class");
            jobs.push_back(std::make_unique<TJob>(args...));
        }

        ~App();

    private:
        bool CreateWindow(int width, int height, const std::string& title);

        std::string name;
        unsigned int windowWidth, windowHeight;
        unsigned int targetFrameDurationMs = 0.0f;

        std::shared_ptr<graphics::Window> window;
        std::vector<std::unique_ptr<base::Job>> jobs;
        std::shared_ptr<Camera> mainCamera;

        static const unsigned int defaultWindowWidth = 1280;
        static const unsigned int defaultWindowHeight = 720;

        static const unsigned int framesBeforeGc = 100;
    };
}

#endif //SMARTIN3D_APP_H
