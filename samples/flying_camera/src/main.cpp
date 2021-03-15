#include "base/App.h"

#include "CameraMovementJob.h"
#include "XwingDestroyJob.h"

using namespace smartin;

int main() {
    base::App app("Test", 1280, 720);
    app.Init();
    app.SetTargetFPS(120);

    auto camera = app.CreateCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -60.0f, 0.0f));
    app.SetSkybox({
        "cupertin-lake_rt.tga",
        "cupertin-lake_lf.tga",
        "cupertin-lake_up.tga",
        "cupertin-lake_dn.tga",
        "cupertin-lake_bk.tga",
        "cupertin-lake_ft.tga"
    });

    app.AddActor("xwing", "x-wing.obj",
                 glm::vec3(-7.0f, 0.0f, 10.0f),
                 glm::vec3(0.006f, 0.006f, 0.006f));
    app.AddActor("blackhawk", "uh60.obj",
                 glm::vec3(-8.0f, 2.0f, 0.0f),
                 glm::vec3(0.4f, 0.4f, 0.4f),
                 glm::vec3(-90.0f, 0.0f, 0.0f));
    app.AddActor("cone", "cone.obj",
                 glm::vec3(-8.0f, 2.0f, 5.0f));

    app.AddJob<CameraMovementJob>(camera, 10.0f, 1.0f);
    app.AddJob<XwingDestroyJob>();

    app.Run();
}
