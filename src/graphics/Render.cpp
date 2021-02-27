#include "graphics/Render.h"

void smartin::graphics::RenderFor(base::Camera* camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();

    graphics::Skybox* skybox = utils::GetSkybox();
    if (skybox != nullptr) {
        Shader* skyboxShader = utils::GetShader("skybox");
        skyboxShader->Apply();
        skyboxShader->SetActiveTextureUnit("skybox", settings::SkyboxTextureUnit);
        skybox->Apply(settings::SkyboxTextureUnit, view, projection);
    }

    Shader* mainShader = utils::GetShader();   // TODO
    mainShader->Apply();
    mainShader->SetActiveTextureUnit("mainTex", settings::MainTextureUnit);
    mainShader->SetMatrix("projection", projection);
    mainShader->SetMatrix("view", view);

    for (base::Actor* actor : utils::GetAllActors()) {
        if (!actor->IsRenderable() || !IsActorVisible(actor))
            continue;

        glm::mat4 model = actor->GetTransform()->GetModelMatrix();

        mainShader->SetMatrix("model", model);
        actor->Render();
    }

    DisableShaders();
}

bool smartin::graphics::IsActorVisible(smartin::base::Actor *actor) {
    // TODO
    return true;
}
