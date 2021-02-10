#ifndef SMARTIN3D_RENDER_H
#define SMARTIN3D_RENDER_H

#include <vector>

#include "Actor.h"
#include "Camera.h"
#include "Material.h"
#include "Shader.h"

namespace smartin::graphics {
    void RenderFor(base::Camera* camera) {
        glm::mat4 projection = camera->GetProjectionMatrix();
        glm::mat4 view = camera->GetViewMatrix();

        std::vector<Shader*> shaders = GetFullShadersList();

        for (Shader* shader : shaders) {
            std::vector<Material*> materials = GetMaterialsByShader(shader);
            if (materials.empty())
                continue;

            shader->Validate();
            shader->Apply();
            shader->SetMatrix("projection", projection);
            shader->SetMatrix("view", view);

            for (Material* material : materials) {
                std::vector<base::Actor*> actors = base::GetActorsUsingMaterial(material);
                if (actors.empty())
                    continue;

                material->Apply();

                for (base::Actor* actor : actors) {
                    glm::mat4 model = actor->GetTransform()->GetModelMatrix();
                    shader->SetMatrix("model", model);

                    actor->Render();
                }
            }
        }

        DisableShaders();
    }
}

#endif //SMARTIN3D_RENDER_H
