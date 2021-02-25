#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <iostream>
#include <vector>

#include "base/Job.h"
#include "utils/OpenGLContext.h"
#include "graphics/Window.h"
#include "utils/TimeUtils.h"
#include "utils/AssetUtils.h"
#include "utils/Input.h"
#include "graphics/Render.h"

using namespace smartin;

// Variables
graphics::Window* window;
std::vector<base::Job*> jobs;
graphics::Shader* mainShader;
graphics::Skybox* skybox;
base::Camera* mainCamera;

// Awake methods
void CreateScene();
graphics::Window* CreateWindow(int width, int height, const char* title);
void CreateJobs();

// Update methods
void UpdateJobs();
void UpdateScene();

// Destroy methods
void Exit();

int main() {
    // Log
    utils::log::Init(std::cout);

    // Window
    window = CreateWindow(1280, 720, "Test window");

    // Input
    utils::input::mouse::settings::invertYAxis = true;
    utils::input::mouse::settings::showCursor = false;
    utils::input::Init(window);

    // Scene
    mainShader = utils::CreateShader();
    mainCamera = utils::CreateCamera(45.0f, window->GetAspectRatio(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -60.0f, 0.0f));
    CreateScene();

    skybox = utils::CreateSkybox({
        "cupertin-lake_rt.tga",
        "cupertin-lake_lf.tga",
        "cupertin-lake_up.tga",
        "cupertin-lake_dn.tga",
        "cupertin-lake_bk.tga",
        "cupertin-lake_ft.tga"
    });

    // Jobs
    CreateJobs();

    // Main loop
    while (!window->IsAboutToClose()) {
        utils::time::Update();
        utils::input::Update();

        // PreRender
        window->PreRender();

        // Update objects
        UpdateScene();
        UpdateJobs();

        // Render
        graphics::RenderFor(mainCamera);
        window->Render();
    }

    Exit();

    return 0;
}

void CreateScene() {
    utils::CreateActorWithAppearance("xwing", "x-wing.obj", glm::vec3(-7.0f, 0.0f, 10.0f), glm::vec3(0.006f, 0.006f, 0.006f));
    utils::CreateActorWithAppearance("blackhawk", "uh60.obj", glm::vec3(-8.0f, 2.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(-90.0f, 0.0f, 0.0f));
}

void UpdateScene() {
    for (auto actor : utils::GetAllActors())
        actor->Update();
}

graphics::Window* CreateWindow(int width, int height, const char* title) {
    utils::context::InitGLFW();

    graphics::Window* window = new graphics::Window(width, height);
    window->Instantiate(title);

    utils::context::InitGLEW();
    window->Init();

    return window;
}

void Exit() {
    // TODO
}

// Jobs
class CameraMovementJob : public base::Job {
public:
    CameraMovementJob(base::Camera* _camera, float _speed, float _turnSpeed) {
        cameraTransform = _camera->GetTransform();
        speed = _speed;
        turnSpeed = _turnSpeed;
    }

    void Tick() override {
        if (utils::input::keyboard::IsKey(KEY_ESCAPE))
            window->Close();

        glm::vec3 forward = cameraTransform->GetForward();
        glm::vec3 right = cameraTransform->GetRight();
        glm::vec3 up = cameraTransform->GetUp();

        // Keys
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

        if (utils::input::keyboard::IsKey(KEY_W))
            direction += forward;
        if (utils::input::keyboard::IsKey(KEY_S))
            direction -= forward;

        if (utils::input::keyboard::IsKey(KEY_A))
            direction += right;
        if (utils::input::keyboard::IsKey(KEY_D))
            direction -= right;

        if (utils::input::keyboard::IsKey(KEY_R))
            direction += up;
        if (utils::input::keyboard::IsKey(KEY_F))
            direction -= up;

        if (direction != glm::vec3(0.0f, 0.0f, 0.0f)) {
            direction = utils::time::GetDeltaTime() * speed * glm::normalize(direction);
            cameraTransform->Move(direction);
        }

        // Mouse
        glm::vec2 mouseDelta = utils::input::mouse::GetCursorDelta();
        mouseDelta *= turnSpeed;

        float yaw = -mouseDelta.x;
        float pitch = mouseDelta.y;
        if (pitch > 89.0f)
            pitch = 89.0f;
        else if (pitch < -89.0f)
            pitch = -89.0f;

        cameraTransform->Rotate(glm::vec3(pitch, yaw, 0.0f));

    }

private:
    base::Transform* cameraTransform;
    float speed, turnSpeed;
};

void CreateJobs() {
    base::Job* job = new CameraMovementJob(mainCamera, 2.0f, 0.5f);
    jobs.push_back(job);
}

void UpdateJobs() {
    for (auto job : jobs)
        job->Tick();
}
