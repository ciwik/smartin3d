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
    // Main loop
    while (!window->IsAboutToClose()) {
        auto frameEnd = std::chrono::steady_clock::now() + std::chrono::milliseconds(targetFrameDurationMs);

        utils::time::Update();
        if (utils::time::GetFrameCount() % FRAMES_BEFORE_GC == 0)
            utils::CollectGarbage();

        utils::input::Update();

        // PreRender
        window->PreRender();

        // Update objects
        for (auto& actor : utils::GetAllActors())
            actor->Update();

        // Update jobs
        for (const auto& job : jobs)
            job->Tick();

        // Render
        graphics::RenderFor(mainCamera);
        window->Render();

        if (utils::input::keyboard::IsKey(KEY_ESCAPE))
            Close();

        std::this_thread::sleep_until(frameEnd);
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
    utils::context::InitGLFW();

    window = std::make_shared<graphics::Window>(width, height);
    if (!window->Instantiate(title)) {
        window.reset();
        return false;
    }

    utils::context::InitGLEW();
    window->Init();
    return true;
}

void smartin::base::App::CreateCamera(const glm::vec3& position, const glm::vec3& eulerAngles, float fov) {
    mainCamera = utils::CreateCamera(fov, window->GetAspectRatio(), position, eulerAngles);
}

void smartin::base::App::SetSkybox(const std::array<std::string, 6>& faceTexturePaths) {
    if (utils::GetShader(utils::DEFAULT_SKY_SHADER_NAME) == nullptr)
        utils::CreateShader(utils::DEFAULT_SKY_SHADER_NAME);

    utils::CreateSkybox(faceTexturePaths);
}

void smartin::base::App::AddJob(std::unique_ptr<smartin::base::Job> job) {
    jobs.push_back(std::move(job));
}

void smartin::base::App::AddActor(const std::string& name, const std::string& modelFileName, const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles) {
    if (utils::GetShader(utils::DEFAULT_SHADER_NAME) == nullptr)
        utils::CreateShader(utils::DEFAULT_SHADER_NAME);

    utils::CreateActorWithAppearance(name, modelFileName, position, size, eulerAngles);
}

void smartin::base::App::SetTargetFPS(unsigned int fps) {
    targetFrameDurationMs = 1000 / fps;
}

