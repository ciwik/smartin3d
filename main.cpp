#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <iostream>
#include <vector>

#include "Job.h"
#include "Actor.h"
#include "OpenGLContext.h"
#include "Window.h"
#include "TimeUtils.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
#include "Render.h"

using namespace smartin;

// Variables
graphics::Window* window;
std::vector<base::Actor*> actors;
std::vector<base::Job*> jobs;
graphics::Shader* mainShader;
base::Camera* mainCamera;

// Awake methods
void CreateScene();
graphics::Window* CreateWindow(int width, int height, const char* title);
base::Camera* CreateCamera(float fov, float aspect, glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3()) ;
graphics::Shader* CreateShader(const char *vertexCodePath, const char *fragmentCodePath);
void CreateJobs();

// Update methods
void UpdateJobs();
void UpdateScene();
void Render();
void RenderScene();

// Destroy methods
void Exit();


int main() {
    utils::log::Init(std::cout);

    utils::input::mouse::settings::invertYAxis = true;

    window = CreateWindow(1280, 720, "Test window");
    mainShader = CreateShader("shaders/default.vshader", "shaders/default.fshader");
    mainCamera = CreateCamera(45.0f, window->GetWidth() / (float) window->GetHeight(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -60.0f, 0.0f));

    CreateScene();
    //CreateJobs();

    // Main loop
    while (!window->IsAboutToClose()) {
        utils::time::Update();
        utils::input::Update();

        // PreRender
        window->PreRender();

        // Update objects
        UpdateScene();
        //UpdateJobs();

        // Render
        graphics::RenderFor(mainCamera);
        window->Render();
    }

    Exit();

    return 0;
}

void CreateScene() {
    unsigned int indices[] = {
            0, 2, 1,
            1, 2, 3,
    };

    GLfloat vertices[] = {
            // X     Y     Z		 U	   V		 Xn	   Yn	 Zn
            -10.0f, 0.0f, -10.0f,	 0.0f,  0.0f,	0.0f, -1.0f, 0.0f,
            10.0f, 0.0f, -10.0f,	10.0f,  0.0f,	0.0f, -1.0f, 0.0f,
            -10.0f, 0.0f,  10.0f,	 0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
            10.0f, 0.0f,  10.0f,	10.0f, 10.0f,	0.0f, -1.0f, 0.0f,
    };

    graphics::Mesh* mesh = new graphics::Mesh();
    mesh->Init(vertices, indices, 32, 6);

    graphics::Material* material = new graphics::Material(mainShader);
    base::Transform* transform = new base::Transform(glm::vec3(0.0f, 1.0f, -0.5f), glm::vec3(0.4f, 0.4f, 1.0f));

    base::Actor* actor = new base::Actor(mesh, material, transform);
    actors.push_back(actor);
}

void UpdateScene() {
    for (auto actor : actors)
        actor->Update();
}

void RenderScene() {
    for (auto actor : actors)
        actor->Render();
}

graphics::Window* CreateWindow(int width, int height, const char* title) {
    utils::context::InitGLFW();

    graphics::Window* window = new graphics::Window(width, height);
    window->Instantiate(title);

    utils::context::InitGLEW();
    window->Init();

    utils::input::RegisterEventListener(window);

    return window;
}

base::Camera* CreateCamera(float fov, float aspect, glm::vec3 pos, glm::vec3 rot) {
    base::Transform* transform = new base::Transform(pos, glm::vec3(0.0f, 0.0f, 0.0f), rot);
    base::Camera* camera = new base::Camera(transform);
    camera->aspect = aspect;
    camera->fieldOfView = fov;

    actors.push_back(camera);
    return camera;
}

graphics::Shader* CreateShader(const char *vertexCodePath, const char *fragmentCodePath) {
    graphics::Shader* shader = graphics::ReadShaderFromFiles(vertexCodePath, fragmentCodePath);
    shader->Compile();
    shader->Validate();

    return shader;
}

void Render() {
    RenderScene();
    window->Render();
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

        float yaw = mouseDelta.x;
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
