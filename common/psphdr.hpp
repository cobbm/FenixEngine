#pragma once

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psprtc.h>
#include <pspmath.h>
#include <stdlib.h>
#include <stdio.h>
// #include <math.h>
#include <cmath>
#include <string.h>

#include <pspgu.h>
#include <pspgum.h>
// #include <pspgum_vfpu.h>

// #include <psprtc.h>

// #include <pspsysmem_kernel.h>

#include "callbacks.hpp"
#include "vram.hpp"
// #include "../common/menu.h"

#define printf(...) pspDebugScreenPrintf(__VA_ARGS__)

extern int thid;