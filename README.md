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
### Loading actor from file
Put the name of the actor, the name of a 3D model file located in the "assets/models" subdirectory, and (optionally) position, size, and rotation (in Euler angles) of the actor.
```
app.AddActor("cone", "cone.obj",
             vec3(-8.0f, 2.0f, 5.0f),
             vec3(0.4f, 0.4f, 0.4f),
             vec3(-90.0f, 0.0f, 0.0f));
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
### Camera creation
Put position, rotation in Euler angles, and field of view.
```
app.CreateCamera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, -60.0f, 0.0f), 45.0f);
```
### Job description
Create a job class inherited from the ```base::Job```, override ```Tick()``` method called every frame before rendering pass.
```
class CameraMovementJob : public smartin::base::Job
```
### Job registration
Put an instance of the custom job to the application.
```
app.AddJob(make_unique<CameraMovementJob>(app.GetCamera(), 10.0f, 1.0f));
```
### Start application
```
app.Run();
```
### Getting delta time
```
smartin::utils::time::GetDeltaTime();
```
### Checking if key is pressed
```
if (utils::input::keyboard::IsKey(utils::input::space))
```
### Checking if key was pressed down on current frame
```
if (utils::input::keyboard::IsKeyDown(utils::input::space))
```
### Checking if key was released
```
if (utils::input::keyboard::IsKeyUp(utils::input::space))
```
### Full job example
This job controls input and provides camera movement.
```
class CameraMovementJob : public base::Job {
public:
    CameraMovementJob(std::shared_ptr<base::Camera> camera, float _speed, float _turnSpeed) :
        cameraTransform(camera->GetTransform()),
        speed(_speed),
        turnSpeed(_turnSpeed) { }

    void Tick() override {
        glm::vec3 forward = cameraTransform->GetForward();
        glm::vec3 right = cameraTransform->GetRight();
        glm::vec3 up = cameraTransform->GetUp();

        // Keys
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

        if (utils::input::keyboard::IsKey(utils::input::w))
            direction += forward;
        if (utils::input::keyboard::IsKey(utils::input::s))
            direction -= forward;

        if (utils::input::keyboard::IsKey(utils::input::a))
            direction += right;
        if (utils::input::keyboard::IsKey(utils::input::d))
            direction -= right;

        if (utils::input::keyboard::IsKey(utils::input::r))
            direction += up;
        if (utils::input::keyboard::IsKey(utils::input::w))
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
```
