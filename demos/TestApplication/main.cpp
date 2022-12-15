#include "psphdr.hpp"
#include "TestApplication.hpp"

PSP_MODULE_INFO("FenixEngine Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

PSP_HEAP_SIZE_KB(1024 * 4);
PSP_MAIN_THREAD_STACK_SIZE_KB(1024 * 4);

int thid = -1;
int main()
{
    // pspDebugInstallErrorHandler(NULL);
    thid = setupCallbacks();

    TestApplication app;
    app.run();

    sceKernelExitGame();
}