#include "graphics/Render.h"

void smartin::graphics::RenderFor(base::Camera* camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();

    std::vector<base::Actor*> actors = utils::GetAllActors();
    for (base::Actor* actor : actors) {
        if (!actor->IsRenderable() || !IsActorVisible(actor))
            continue;

        glm::mat4 model = actor->GetTransform()->GetModelMatrix();

        Shader* shader = utils::GetShader("default");   // TODO
        shader->Validate();
        shader->Apply();
        shader->SetMatrix("projection", projection);
        shader->SetMatrix("view", view);
        shader->SetMatrix("model", model);

        actor->Render();
    }

    DisableShaders();
}

bool smartin::graphics::IsActorVisible(smartin::base::Actor *actor) {
    // TODO
    return true;
}
