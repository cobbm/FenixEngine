#include "Application.hpp"

#ifdef PSP
bool platformShouldQuit()
{
    return !running();
}

#endif