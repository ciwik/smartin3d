#ifndef SMARTIN3D_RENDER_H
#define SMARTIN3D_RENDER_H

#include "precompiled.h"

#include "base/Actor.h"
#include "base/Camera.h"
#include "graphics/Material.h"
#include "graphics/Shader.h"
#include "graphics/Settings.h"
#include "utils/AssetUtils.h"

namespace smartin::graphics {
    bool IsActorVisible(std::shared_ptr<base::Actor> actor);
    void RenderFor(std::shared_ptr<base::Camera> camera);
}

#endif //SMARTIN3D_RENDER_H
