#ifndef SMARTIN3D_RENDER_H
#define SMARTIN3D_RENDER_H

#include <vector>

#include "base/Actor.h"
#include "base/Camera.h"
#include "graphics/Material.h"
#include "Shader.h"

namespace smartin::graphics {
    bool IsActorVisible(base::Actor* actor);
    void RenderFor(base::Camera* camera);
}

#endif //SMARTIN3D_RENDER_H
