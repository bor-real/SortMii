#pragma once

#include <vector>
#include <grrlib.h>
#include <string>

#define WIDTH 640
#define HEIGHT 480

class Visualizer {
public:
    Visualizer() {}

    void draw(std::vector<int> v) {
        GRRLIB_FillScreen(0x000000FF);
        int numBars = v.size();
        int totalGapWidth = numBars - 1; // Total width of the gaps between bars
        int barWidth = (WIDTH - totalGapWidth) / numBars; // Adjusted bar width with gaps
        unsigned int index = 0;

        for (unsigned int i : v) {
            // Calculate bar height relative to the screen height
            int barHeight = (i * HEIGHT) / getMaxValue(v);
            int x = index * (barWidth + 1); // Calculate the x position with the gap
            GRRLIB_Rectangle(x, HEIGHT - barHeight, barWidth, barHeight, 0xFFFFFFFF, 1);
            index++;
        }

        GRRLIB_Render();
    }

private:
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
