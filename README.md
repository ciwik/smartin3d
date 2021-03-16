# smartin3d
Modest 3D game engine, written only for educational purposes.

Currently, this project runs on Windows, but may also be built for Linux and Mac OS if the required libraries exist on the system. It requires GLEW, GLFW, GLM, assimp. Paths to these libraries can be set manually as command line arguments to cmake, i.e. ```cmake . -DGLEW_ROOT=... -DGLFW32_ROOT=... -DGLM_ROOT=... -DASSIMP_ROOT=...```.

## Code snippets
### App creation
Simply create an ```App``` object, put the application name and windows size in the constructor, and call the ```Init()``` method.
```
smartin::base::App app("App name", 1280, 720);
app.Init();
```
### Actor creation
Put the name of the actor and (optionally) position, size, and rotation (in Euler angles) of the actor.
```
smartin::utils::CreateActor("actor",
                            vec3(-8.0f, 2.0f, 5.0f),
                            vec3(0.4f, 0.4f, 0.4f),
                            vec3(-90.0f, 0.0f, 0.0f));
```
### Camera creation
Put position, rotation in Euler angles, and field of view.
```
app.CreateCamera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, -60.0f, 0.0f), 45.0f);
```
### Loading actor from file
Put the name of the actor, the name of a 3D model file located in the "assets/models" subdirectory, and (optionally) position, size, and rotation (in Euler angles) of the actor.
```
smartin::utils::CreateActorWithAppearance("cone", "cone.obj",
                                          vec3(-8.0f, 2.0f, 5.0f),
                                          vec3(0.4f, 0.4f, 0.4f),
                                          vec3(-90.0f, 0.0f, 0.0f));
```
or just
```
app.AddActor("cone", "cone.obj",
             vec3(-8.0f, 2.0f, 5.0f),
             vec3(0.4f, 0.4f, 0.4f),
             vec3(-90.0f, 0.0f, 0.0f));
```
### Search over actors and assets
```
auto cone = smartin::utils::FindActor("cone");
```
```
auto material = smartin::utils::GetMaterial("cone_mat");
```
### Actor destroyment
```
smartin::utils::DestroyActor(smartin::utils::FindActor("cone"));
```
### Loading skybox
Put names of 6 skybox textures located in the "assets/textures/skyboxes" subdirectory.
```
app.SetSkybox({
  "skybox_rt.tga",
  "skybox_lf.tga",
  "skybox_up.tga",
  "skybox_dn.tga",
  "skybox_bk.tga",
  "skybox_ft.tga"
});
```
### Setting target FPS
```
app.SetTargetFPS(120);
```
### Job description
Create a job class inherited from the ```base::Job```, override ```Tick()``` method called every frame before rendering pass.
```
class CameraMovementJob : public smartin::base::Job
```
### Job registration
Put an instance of the custom job to the application.
```
app.AddJob<CameraMovementJob>(app.GetCamera(), 10.0f, 1.0f);
```
### Start application
```
app.Run();
```
### Getting delta time
```
auto dt = smartin::utils::time::GetDeltaTime();
```
### Checking if key is pressed
```
if (smartin::utils::input::keyboard::IsKey(smartin::utils::input::space))
```
### Checking if key was pressed down on current frame
```
if (smartin::utils::input::keyboard::IsKeyDown(smartin::utils::input::space))
```
### Checking if key was released on current frame
```
if (smartin::utils::input::keyboard::IsKeyUp(smartin::utils::input::space))
```
### Job example
This job processes the input and provides camera movement.
```
class CameraMovementJob : public smartin::base::Job {
public:
    CameraMovementJob(shared_ptr<smartin::base::Camera> camera, float _speed, float _turnSpeed) :
        cameraTransform(camera->GetTransform()),
        speed(_speed),
        turnSpeed(_turnSpeed) { }

    void Tick() override {
        vec3 forward = cameraTransform->GetForward();
        vec3 right = cameraTransform->GetRight();
        vec3 up = cameraTransform->GetUp();

        // Keys
        vec3 direction = vec3(0.0f, 0.0f, 0.0f);

        if (smartin::utils::input::keyboard::IsKey(smartin::utils::input::w))
            direction += forward;
        if (smartin::utils::input::keyboard::IsKey(smartin::utils::input::s))
            direction -= forward;

        if (smartin::utils::input::keyboard::IsKey(smartin::utils::input::a))
            direction += right;
        if (smartin::utils::input::keyboard::IsKey(smartin::utils::input::d))
            direction -= right;

        if (smartin::utils::input::keyboard::IsKey(smartin::utils::input::r))
            direction += up;
        if (smartin::utils::input::keyboard::IsKey(smartin::utils::input::w))
            direction -= up;

        direction = smartin::utils::time::GetDeltaTime() * speed * normalize(direction);
        cameraTransform->Move(direction);

        // Mouse
        vec2 mouseDelta = smartin::utils::input::mouse::GetCursorDelta();
        mouseDelta *= turnSpeed;

        float yaw = -mouseDelta.x;
        float pitch = mouseDelta.y;
        if (pitch > 89.0f)
            pitch = 89.0f;
        else if (pitch < -89.0f)
            pitch = -89.0f;

        cameraTransform->Rotate(vec3(pitch, yaw, 0.0f));
    }

private:
    shared_ptr<smartin::base::Transform> cameraTransform;
    float speed, turnSpeed;
};
```
### main() example
```
int main() {
    smartin::base::App app("App name", 1280, 720);
    app.Init();
    app.SetTargetFPS(120);

    auto camera = app.CreateCamera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, -60.0f, 0.0f));
    app.SetSkybox({
      "skybox_rt.tga",
      "skybox_lf.tga",
      "skybox_up.tga",
      "skybox_dn.tga",
      "skybox_bk.tga",
      "skybox_ft.tga"
    });

    app.AddActor("xwing", "x-wing.obj",
                 vec3(-7.0f, 0.0f, 10.0f),
                 vec3(0.006f, 0.006f, 0.006f));
    app.AddActor("cone", "cone.obj",
                 vec3(-8.0f, 2.0f, 5.0f));

    app.AddJob<CameraMovementJob>(camera, 10.0f, 1.0f);

    app.Run();
}
```
