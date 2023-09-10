#pragma once

#include <wiiuse/wpad.h>
#include <grrlib.h>

#include <vector>
#include <random>
#include <algorithm>
#include <string>

#include "Visualizer.h"
#include "Algorithms.h"

class SortMii {
public:
    void randomize(int amount) {
        v.clear();

        for (int i = 0; i < amount; i++) {
            v.push_back(d(rd));
        }
    }

    SortMii(int amount) : rd(), d(1, amount), bubble(v)  {
        randomize(amount);

        while(1) {
            WPAD_ScanPads();

            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS)  {
                amount += 5;
                randomize(amount);
                bubble.reset();
            }
            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_MINUS)  {
                amount -= 5;
                randomize(amount);
                bubble.reset();
            }

            bubble.step(v);
            vis.draw(v);
        }
    }
private:
    std::random_device rd;
    std::uniform_int_distribution<int> d;
    std::vector<int> v;

    Visualizer vis;
    
    BubbleSort bubble;
};
