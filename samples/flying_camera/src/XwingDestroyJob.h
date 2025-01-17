#ifndef SMARTIN3D_XWINGDESTROYJOB_H
#define SMARTIN3D_XWINGDESTROYJOB_H

#include "base/App.h"

using namespace smartin;

class XwingDestroyJob : public base::Job {
public:
    void Tick() override {
        if (utils::input::keyboard::IsKeyDown(utils::input::space))
            utils::DestroyActor(utils::FindActor("xwing"));

        if (utils::input::keyboard::IsKeyDown(utils::input::l_shift))
            utils::DestroySkybox();

        if (utils::input::keyboard::IsKeyDown(utils::input::l_ctrl))
            utils::DebugPrintContent();
    }
};

#endif //SMARTIN3D_XWINGDESTROYJOB_H
