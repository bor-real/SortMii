#pragma once

#include "Rockwell_Condensed_12_Bold_png.h"

#include <vector>
#include <grrlib.h>
#include <string>

#include "AlgorithmInfo.h"

#define WIDTH 640
#define HEIGHT 480

#define VERSION "0.3.0"

class Visualizer {
public:
    Visualizer() {
        tex_font = GRRLIB_LoadTexture(Rockwell_Condensed_12_Bold_png);
        GRRLIB_InitTileSet(tex_font, 12, 19, 32);
    }

    ~Visualizer() {
        GRRLIB_FreeTexture(tex_font);
    }

    void draw(std::vector<int> v, AlgorithmInfo ai, std::string name) {
        GRRLIB_FillScreen(0x000000FF);
        int numBars = v.size();
        int totalGapWidth = numBars - 1;
        int barWidth = (WIDTH - totalGapWidth) / numBars;
        int index = 0;

        for (unsigned int i : v) {
            int barHeight = (i * HEIGHT) / getMaxValue(v);
            int x = index * (barWidth + 1);

            // Determine the color for the current bar
            u32 barColor = 0xFFFFFFFF;  // Default color
            if (index == ai.redPos) {
                barColor = 0xFF0000FF;
            } else if (index == ai.bluePos && ai.bluePos > 0) {
                barColor = 0x0000FFFF;
            } else {
                barColor = 0xFFFFFFFF;
            }

            GRRLIB_Rectangle(x, HEIGHT - barHeight, barWidth, barHeight, barColor, 1);
            index++;
        }

        // Move on to drawing the text

        GRRLIB_Rectangle(0, 0, WIDTH, HEIGHT * 0.1, 0x000000BB, 1);
        GRRLIB_Printf(20, 20, tex_font, 0xFFFFFFFF, 1, "SortMii %s, %s, %d ACS, %d CMP",
            VERSION, name.c_str(), ai.accesses, ai.comparisons);

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
