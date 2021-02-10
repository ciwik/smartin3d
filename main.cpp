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

void calcAverageNormals(unsigned int* indices, unsigned int indexNumber, GLfloat* vertices, unsigned int vertexNumber, unsigned int vLength, unsigned int normalOffset)
{
    for (size_t i = 0; i < indexNumber; i += 3) {
        unsigned int i0 = indices[i] * vLength;
        unsigned int i1 = indices[i + 1] * vLength;
        unsigned int i2 = indices[i + 2] * vLength;

        glm::vec3 v1(vertices[i1] - vertices[i0], vertices[i1 + 1] - vertices[i0 + 1], vertices[i1 + 2] - vertices[i0 + 2]);
        glm::vec3 v2(vertices[i2] - vertices[i0], vertices[i2 + 1] - vertices[i0 + 1], vertices[i2 + 2] - vertices[i0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        i0 += normalOffset;
        i1 += normalOffset;
        i2 += normalOffset;

        vertices[i0] += normal.x;
        vertices[i0 + 1] += normal.y;
        vertices[i0 + 2] += normal.z;

        vertices[i1] += normal.x;
        vertices[i1 + 1] += normal.y;
        vertices[i1 + 2] += normal.z;

        vertices[i2] += normal.x;
        vertices[i2 + 1] += normal.y;
        vertices[i2 + 2] += normal.z;
    }

    for (size_t i = 0; i < vertexNumber / vLength; i++) {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 v(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        v = glm::normalize(v);

        vertices[nOffset] = v.x;
        vertices[nOffset + 1] = v.y;
        vertices[nOffset + 2] = v.z;
    }
}

void CreateScene() {
    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            // X     Y     Z			 U	   V		 Xn	   Yn	 Zn
            -1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
            0.0f, -1.0f,  1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
            0.0f,  1.0f,  0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f,
    };
    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    graphics::Mesh* mesh = new graphics::Mesh();
    mesh->Init(vertices, indices, 32, 12);

    graphics::Texture* dirtTex = new graphics::Texture("textures/dirt.png", true);
    dirtTex->Load();

    graphics::Material* material = new graphics::Material(mainShader);
    material->SetTexture(dirtTex);
    material->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

    base::Transform* transform = new base::Transform(glm::vec3(0.0f, 0.0f, -5.5f));

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
