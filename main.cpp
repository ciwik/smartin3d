#include "base/App.h"

using namespace smartin;

class CameraMovementJob : public base::Job {
public:
    CameraMovementJob(std::shared_ptr<base::Camera> camera, float _speed, float _turnSpeed) {
        cameraTransform = camera->GetTransform();
        speed = _speed;
        turnSpeed = _turnSpeed;
    }

    void Tick() override {
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
    std::shared_ptr<base::Transform> cameraTransform;
    float speed, turnSpeed;
};

class XwingDestroyJob : public base::Job {
public:
    void Tick() override {
        if (utils::input::keyboard::IsKeyDown(KEY_SPACE))
            utils::DestroyActor(utils::FindActor("xwing"));

        if (utils::input::keyboard::IsKeyDown(KEY_LEFT_SHIFT))
            utils::DestroySkybox();
    }
};

int main() {
    auto app = new base::App("Test", 1280, 720);
    app->Init();

    app->CreateCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -60.0f, 0.0f));
    app->SetSkybox({
       "cupertin-lake_rt.tga",
       "cupertin-lake_lf.tga",
       "cupertin-lake_up.tga",
       "cupertin-lake_dn.tga",
       "cupertin-lake_bk.tga",
       "cupertin-lake_ft.tga"
    });

    app->AddActor("xwing", "x-wing.obj",
                  glm::vec3(-7.0f, 0.0f, 10.0f),
                  glm::vec3(0.006f, 0.006f, 0.006f));
    app->AddActor("blackhawk", "uh60.obj",
                  glm::vec3(-8.0f, 2.0f, 0.0f),
                  glm::vec3(0.4f, 0.4f, 0.4f),
                  glm::vec3(-90.0f, 0.0f, 0.0f));

    app->AddJob(std::make_unique<CameraMovementJob>(app->GetCamera(), 2.0f, 0.5f));
    app->AddJob(std::make_unique<XwingDestroyJob>());

    app->Run();
    delete app;

    return 0;
}
