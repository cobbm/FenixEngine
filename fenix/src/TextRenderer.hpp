#pragma once
#include "../../src/psphdr.hpp"
#include "font.c"
/*
    This function draws a string on the screen
    The chars are handled as sprites.
    It supportes colors and blending.
    The fontwidth can be selected with the parameter fw, if it is 0 the best width for each char is selected.
*/
namespace Fenix
{
    extern int fontwidthtab[128];

    void drawString(const char *, int, int, unsigned int, int = 0);

    unsigned int measureString(const char *, int = 0);
}