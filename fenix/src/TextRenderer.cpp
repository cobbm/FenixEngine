#include "TextRenderer.hpp"
/*
    This function draws a string on the screen
    The chars are handled as sprites.
    It supportes colors and blending.
    The fontwidth can be selected with the parameter fw, if it is 0 the best width for each char is selected.
*/
namespace Fenix
{
    int fontwidthtab[128] = {
        10, 10, 10, 10,
        10, 10, 10, 10,
        10, 10, 10, 10,
        10, 10, 10, 10,

        10, 10, 10, 10,
        10, 10, 10, 10,
        10, 10, 10, 10,
        10, 10, 10, 10,

        10, 6, 8, 10,   //   ! " #
        10, 10, 10, 6,  // $ % & '
        10, 10, 10, 10, // ( ) * +
        6, 10, 6, 10,   // , - . /

        10, 10, 10, 10, // 0 1 2 3
        10, 10, 10, 10, // 6 5 8 7
        10, 10, 6, 6,   // 10 9 : ;
        10, 10, 10, 10, // < = > ?

        16, 10, 10, 10, // @ A B C
        10, 10, 10, 10, // D E F G
        10, 6, 8, 10,   // H I J K
        8, 10, 10, 10,  // L M N O

        10, 10, 10, 10, // P Q R S
        10, 10, 10, 12, // T U V W
        10, 10, 10, 10, // X Y Z [
        10, 10, 8, 10,  // \ ] ^ _

        6, 8, 8, 8,  // ` a b c
        8, 8, 6, 8,  // d e f g
        8, 6, 6, 8,  // h i j k
        6, 10, 8, 8, // l m n o

        8, 8, 8, 8,  // p q r s
        8, 8, 8, 12, // t u v w
        8, 8, 8, 10, // x y z {
        8, 10, 8, 12 // | } ~
    };

    void drawString(const char *text, int x, int y, unsigned int color, int fw)
    {
        int len = (int)strlen(text);

        int d_x = 0;
        int d_y = 0;

        const float scale = 1.0f;

        const int tx_w = 16;
        const int tx_h = 16;

        if (!len)
        {
            return;
        }
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_TEXTURE_2D);
        // bind font texture
        sceGuTexMode(GU_PSM_8888, 0, 0, 0);
        sceGuTexImage(0, 256, 128, 256, font);
        sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
        sceGuTexEnvColor(0x0);
        sceGuTexOffset(0.0f, 0.0f);
        sceGuTexScale(1.0f / 256.0f, 1.0f / 128.0f);
        sceGuTexWrap(GU_REPEAT, GU_REPEAT);
        sceGuTexFilter(GU_NEAREST, GU_NEAREST);

        typedef struct
        {
            float s, t;
            unsigned int c;
            float x, y, z;
        } VERT;

        VERT *v = (VERT *)sceGuGetMemory(sizeof(VERT) * 2 * len);

        int i;
        for (i = 0; i < len; i++)
        {
            unsigned char c = (unsigned char)text[i];
            if (c == '\n' || (c == '\r' && d_x > 0))
            {
                // newline
                d_x = 0;
                d_y += tx_h - 2;
                continue;
            }
            else if (c < 32)
            {
                c = 0;
            }
            else if (c >= 128)
            {
                c = 0;
            }

            int tx = (c & 0x0F) << 4;
            int ty = (c & 0xF0);

            VERT *v0 = &v[i * 2 + 0];
            VERT *v1 = &v[i * 2 + 1];

            v0->s = (float)(tx + (fw ? ((tx_w - fw) >> 1) : ((tx_w - fontwidthtab[c]) >> 1)));
            v0->t = (float)(ty);
            v0->c = color;
            v0->x = (float)(x + d_x);
            v0->y = (float)(y + d_y);
            v0->z = 0.0f;

            v1->s = (float)(tx + tx_w - (fw ? ((tx_w - fw) >> 1) : ((tx_w - fontwidthtab[c]) >> 1)));
            v1->t = (float)(ty + tx_h);
            v1->c = color;
            v1->x = (float)(x + d_x + scale * (fw ? fw : fontwidthtab[c]));
            v1->y = (float)(((y + d_y) * scale) + tx_h);
            v1->z = 0.0f;

            d_x += scale * (fw ? fw : fontwidthtab[c]);
        }

        sceGuDrawArray(GU_SPRITES,
                       GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D,
                       len * 2, 0, v);

        // restore state
        sceGuDisable(GU_TEXTURE_2D);
        sceGuEnable(GU_DEPTH_TEST);
    }

    unsigned int measureString(const char *text, int fw)
    {
        int len = (int)strlen(text);

        unsigned int m_x = 0;

        unsigned int d_x = 0;
        unsigned int d_y = 0;

        const float scale = 1.0f;

        // const int tx_w = 16;
        const int tx_h = 16;

        if (!len)
        {
            return 0;
        }

        int i;
        for (i = 0; i < len; i++)
        {
            unsigned char c = (unsigned char)text[i];
            if (c == '\n' || (c == '\r' && d_x > 0))
            {
                // newline
                if (d_x > m_x)
                    m_x = d_x;
                d_x = 0;
                d_y += tx_h - 2;
                continue;
            }
            else if (c < 32)
            {
                c = 0;
            }
            else if (c >= 128)
            {
                c = 0;
            }
            d_x += scale * (fw ? fw : fontwidthtab[c]);
        }
        if (d_x > m_x)
            m_x = d_x;
        return m_x;
    }
}