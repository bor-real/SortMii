#pragma once

#include "Rockwell_Condensed_12_Bold_png.h"

#include <vector>
#include <grrlib.h>
#include <string>

#define WIDTH 640
#define HEIGHT 480

#define VERSION "0.2.0"

class Visualizer {
public:
    Visualizer() {
        tex_font = GRRLIB_LoadTexture(Rockwell_Condensed_12_Bold_png);
        GRRLIB_InitTileSet(tex_font, 12, 19, 32);
    }

    ~Visualizer() {
        GRRLIB_FreeTexture(tex_font);
    }

    void draw(std::vector<int> v, std::string name) {
        GRRLIB_FillScreen(0x000000FF);
        int numBars = v.size();
        int totalGapWidth = numBars - 1;
        int barWidth = (WIDTH - totalGapWidth) / numBars;
        unsigned int index = 0;

        for (unsigned int i : v) {

            int barHeight = (i * HEIGHT) / getMaxValue(v);
            int x = index * (barWidth + 1);
            GRRLIB_Rectangle(x, HEIGHT - barHeight, barWidth, barHeight, 0xFFFFFFFF, 1);
            index++;
        }

        //move on to drawing the text

        GRRLIB_Rectangle(0, 0, WIDTH, HEIGHT * 0.1, 0x000000BB, 1);
        GRRLIB_Printf(20, 20, tex_font, 0xFFFFFFFF, 1, "SortMii %s, %s", VERSION, name.c_str());

        GRRLIB_Render();
    }

private:
    GRRLIB_texImg *tex_font;

    int getMaxValue(const std::vector<int>& v) {
        int max = 0;
        for (int value : v) {
            if (value > max) {
                max = value;
            }
        }
        return max;
    }
};
