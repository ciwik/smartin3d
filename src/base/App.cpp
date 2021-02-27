#include "base/App.h"

smartin::base::App::App(const std::string& _name, unsigned int width, unsigned int height) {
    name = _name;
    windowWidth = width;
    windowHeight = height;
}

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
        utils::time::Update();
        utils::input::Update();

        // PreRender
        window->PreRender();

        // Update objects
        for (Actor* actor : utils::GetAllActors())
            actor->Update();

        // Update jobs
        for (Job* job : jobs)
            job->Tick();

        // Render
        graphics::RenderFor(mainCamera);
        window->Render();

        if (utils::input::keyboard::IsKey(KEY_ESCAPE))
            Close();
    }
}

void smartin::base::App::Close() {
    window->Close();
}

smartin::base::App::~App() {
    // TODO: Use utils::DestroyXXX()
    for (Actor* actor : utils::GetAllActors())
        delete actor;

    for (Job* job : jobs)
        delete job;
}

bool smartin::base::App::CreateWindow(int width, int height, const std::string &title) {
    utils::context::InitGLFW();

    window = new graphics::Window(width, height);
    if (!window->Instantiate(title)) {
        delete window;
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
    if (utils::GetShader(DEFAULT_SKY_SHADER_NAME) == nullptr)
        utils::CreateShader(DEFAULT_SKY_SHADER_NAME);

    utils::CreateSkybox(faceTexturePaths);
}

void smartin::base::App::AddJob(smartin::base::Job* job) {
    jobs.push_back(job);
}

void smartin::base::App::AddActor(const std::string& name, const std::string& modelFileName, const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles) {
    if (utils::GetShader(DEFAULT_SHADER_NAME) == nullptr)
        utils::CreateShader(DEFAULT_SHADER_NAME);

    utils::CreateActorWithAppearance(name, modelFileName, position, size, eulerAngles);
}

