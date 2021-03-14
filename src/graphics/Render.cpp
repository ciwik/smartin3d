#include "graphics/Render.h"

void smartin::graphics::RenderFor(std::shared_ptr<base::Camera> camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();

    // Skybox
    auto skybox = utils::GetSkybox();
    if (skybox != nullptr) {
        auto skyboxShader = utils::GetShader(graphics::skyboxShaderName);
        skyboxShader->Apply();
        skyboxShader->SetActiveTextureUnit(graphics::skyboxShaderName, settings::SkyboxTextureUnit);
        skybox->Apply(settings::SkyboxTextureUnit, view, projection);
    }

    // Shader
    auto mainShader = utils::GetShader(graphics::defaultShaderName);
    mainShader->Apply();
    mainShader->SetActiveTextureUnit("mainTex", settings::MainTextureUnit);
    mainShader->SetMatrix("projection", projection);
    mainShader->SetMatrix("view", view);

    // Lighting
    for (const auto& light : utils::GetAllLights())
        light->ApplyTo(mainShader);

    const auto& mainLight = utils::GetMainLight();
    if (mainLight != nullptr) {
        mainLight->shadowMap->Read(settings::ShadowMapTextureUnit);
        mainShader->SetActiveTextureUnit("directionalShadowMap", settings::ShadowMapTextureUnit);
    }

    // Actors
    for (const auto& actor : utils::GetAllActors()) {
        if (!actor->IsRenderable() || !IsActorVisible(actor))
            continue;

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
