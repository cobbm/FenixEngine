#include "../../src/psphdr.hpp"

#include <malloc.h>

PSP_MODULE_INFO("FenixEngine Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

PSP_HEAP_SIZE_KB(1024 * 4);
PSP_MAIN_THREAD_STACK_SIZE_KB(1024 * 4);

typedef ScePspQuatMatrix _QuaternionF;

typedef struct alignas(32) QuaternionF : public _QuaternionF
{
} QuaternionF;

ScePspQuatMatrix eulerToQuaternion(const ScePspFVector3 &euler)
{
    // Vector3F eulerAl __attribute__((aligned(16))) = euler;

    // ScePspQuatMatrix out __attribute__((aligned(32))); //= QuaternionF{0, 0, 0, 1};
    // alignas(4 * 8) ScePspQuatMatrix out;

    // ScePspQuatMatrix *out2 = (ScePspQuatMatrix *)__builtin_alloca_with_align(sizeof(ScePspQuatMatrix), 16 * 8);
    //  ScePspQuatMatrix *out2;
    //  out2 = (ScePspQuatMatrix *)memalign(16, sizeof(ScePspQuatMatrix));

    // x and y are swapped?
    // vfpu_quaternion_from_euler(&out, 0.0f, 0.0f, 0.0f);

    // ScePspQuatMatrix *q = &out;

    QuaternionF out;
    QuaternionF *q = &out;

    printf("\n\naddr: %p\n\n", q);
    int ptr = (int)q;
    if (ptr % 16 == 0)
    {
        sceDisplayWaitVblank();

        vfpu_quaternion_identity(q);
    }
    else
    {
        printf("NOT ALIGNED: 0x%x\n", ptr);
    }
    return out;
}

int main()
{
    setupCallbacks();

    // pspDebugInstallErrorHandler(nullptr);

    pspDebugScreenInit();

    ScePspQuatMatrix quat_z;

    vfpu_quaternion_identity(&quat_z);

    printf("Direct:\n%f,%f,%f,%f\n", quat_z.x, quat_z.y, quat_z.z, quat_z.w);

    sceDisplayWaitVblank();

    ScePspFVector3 __attribute__((aligned(16))) inp{0, 0, 0};

    ScePspQuatMatrix __attribute__((aligned(16))) quat;

    quat = eulerToQuaternion(inp);
    // vfpu_quaternion_from_euler(&quat, 0, 0, 0);

    printf("\nCall:\n%f,%f,%f,%f\n", quat.x, quat.y, quat.z, quat.w);

    while (running())
    {
    }

    sceKernelExitGame();
}