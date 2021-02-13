#include "graphics/Render.h"

void smartin::graphics::RenderFor(base::Camera* camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();

    std::vector<base::Actor*> actors = base::GetAllActors();
    for (base::Actor* actor : actors) {
        if (!actor->IsRenderable() || !IsActorVisible(actor))
            continue;

        glm::mat4 model = actor->GetTransform()->GetModelMatrix();

        Shader* shader = actor->GetMaterial()->GetShader();
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
