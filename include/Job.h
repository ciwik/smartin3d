#ifndef SMARTIN3D_JOB_H
#define SMARTIN3D_JOB_H

namespace smartin::base {
    class Job {
    public:
        virtual void Tick() = 0;
    };
}
#endif //SMARTIN3D_JOB_H
