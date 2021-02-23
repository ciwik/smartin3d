#include "graphics/Render.h"

void smartin::graphics::RenderFor(base::Camera* camera) {
    Shader* shader = utils::GetShader();   // TODO
    shader->Apply();
    shader->SetActiveTextureUnit("mainTex", settings::MainTextureUnit);

    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();

    shader->SetMatrix("projection", projection);
    shader->SetMatrix("view", view);

    std::vector<base::Actor*> actors = utils::GetAllActors();
    for (base::Actor* actor : actors) {
        if (!actor->IsRenderable() || !IsActorVisible(actor))
            continue;

        glm::mat4 model = actor->GetTransform()->GetModelMatrix();

        shader->SetMatrix("model", model);
        actor->Render();
    }

    DisableShaders();
}

bool smartin::graphics::IsActorVisible(smartin::base::Actor *actor) {
    // TODO
    return true;
}
