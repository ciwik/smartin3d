#include "graphics/Render.h"

void smartin::graphics::RenderFor(std::shared_ptr<base::Camera> camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();

    auto skybox = utils::GetSkybox();
    if (skybox != nullptr) {
        auto skyboxShader = utils::GetShader("skybox");
        skyboxShader->Apply();
        skyboxShader->SetActiveTextureUnit("skybox", settings::SkyboxTextureUnit);
        skybox->Apply(settings::SkyboxTextureUnit, view, projection);
    }

    auto mainShader = utils::GetShader();   // TODO
    mainShader->Apply();
    mainShader->SetActiveTextureUnit("mainTex", settings::MainTextureUnit);
    mainShader->SetMatrix("projection", projection);
    mainShader->SetMatrix("view", view);

    for (auto& actor : utils::GetAllActors()) {
        if (!actor->IsRenderable() || !IsActorVisible(actor))
            continue;

        DisableTextures();

        glm::mat4 model = actor->GetTransform()->GetModelMatrix();

        mainShader->SetMatrix("model", model);
        actor->Render();
    }

    DisableShaders();
}

bool smartin::graphics::IsActorVisible(std::shared_ptr<base::Actor> actor) {
    // TODO
    return true;
}
