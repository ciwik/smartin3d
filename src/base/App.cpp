#include "base/App.h"

smartin::base::App::App(const std::string& _name, unsigned int width, unsigned int height) :
    name(_name),
    windowWidth(width),
    windowHeight(height) { }

void smartin::base::App::Init() {
    // Log
    utils::log::Init(std::cout);

    // Window
    if (!CreateWindow(windowWidth, windowHeight, name))
        return;

    // Input
    utils::input::mouse::settings::invertYAxis = true;
    utils::input::mouse::settings::showCursor = false;
    utils::input::Init(window);
}

void smartin::base::App::Run() {
    try {

        // Main loop
        while (!window->IsAboutToClose()) {
            auto frameEnd = utils::time::GetRealtimeSinceStartup() + std::chrono::milliseconds(targetFrameDurationMs);

            utils::time::Update();
            if (utils::time::GetFrameCount() % framesBeforeGc == 0)
                utils::CollectGarbage();

            utils::input::Update();

            // PreRender
            window->PreRender();

            // Update objects
            for (auto &actor : utils::GetAllActors())
                actor->Update();

            // Update jobs
            for (const auto &job : jobs)
                job->Tick();

            // Render
            graphics::RenderFor(mainCamera);
            window->Render();

            if (utils::input::keyboard::IsKey(utils::input::esc))
                Close();

            if (utils::time::GetRealtimeSinceStartup() < frameEnd)
                std::this_thread::sleep_until(frameEnd);
        }

    } catch (utils::error::SmartinRuntimeException& e) {
        utils::log::E(e);
        Close();
    }
}

void smartin::base::App::Close() {
    window->Close();
}

smartin::base::App::~App() {
    for (auto& actor : utils::GetAllActors())
        utils::DestroyActor(actor);

    jobs.clear();
}

bool smartin::base::App::CreateWindow(int width, int height, const std::string &title) {
    try {
        utils::context::InitGLFW();

        window = std::make_shared<graphics::Window>(width, height);
        window->Instantiate(title);

        utils::context::InitGLEW();
        window->Init();
    } catch (utils::error::SmartinRuntimeException& e) {
        utils::log::E(e);
        window.reset();
        return false;
    }

    return true;
}

void smartin::base::App::CreateCamera(const glm::vec3& position, const glm::vec3& eulerAngles, float fov) {
    mainCamera = utils::CreateCamera(fov, window->GetAspectRatio(), position, eulerAngles);
}

void smartin::base::App::SetSkybox(const std::array<std::string, 6>& faceTexturePaths) {
    if (utils::GetShader(graphics::skyboxShaderName) == nullptr)
        utils::CreateShader(graphics::skyboxShaderName);

    utils::CreateSkybox(faceTexturePaths);
}

void smartin::base::App::AddJob(std::unique_ptr<smartin::base::Job> job) {
    jobs.push_back(std::move(job));
}

void smartin::base::App::AddActor(const std::string& name, const std::string& modelFileName, const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles) {
    if (utils::GetShader(graphics::defaultShaderName) == nullptr)
        utils::CreateShader(graphics::defaultShaderName);

    utils::CreateActorWithAppearance(name, modelFileName, position, size, eulerAngles);
}

void smartin::base::App::SetTargetFPS(unsigned int fps) {
    targetFrameDurationMs = 1000 / fps;
}

void smartin::base::App::AddDirectionalLight(const std::string& name, glm::vec3 direction, bool main, glm::vec3 color,
                                             float ambientIntensity, float diffuseIntensity) {
    if (utils::GetLight(name) == nullptr)
        utils::CreateDirectionalLight(name, color, direction, ambientIntensity, diffuseIntensity, main);
}

