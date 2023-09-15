#pragma once

#include <wiiuse/wpad.h>
#include <grrlib.h>

#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <memory>
#include <iostream>

#include "Visualizer.h"
#include "Algorithms.h"
#include "AlgorithmInfo.h"

class SortMii {
public:
    SortMii(int initialAmount) : rd(), d(1, initialAmount), currentAmount(initialAmount) {
        randomize(initialAmount);

        av.emplace_back(std::make_unique<BubbleSort>(v));
        av.emplace_back(std::make_unique<CocktailShakerSort>(v));
        
        av.emplace_back(std::make_unique<GnomeSort>(v));
        av.emplace_back(std::make_unique<InsertionSort>(v));

        while (true) {
            WPAD_ScanPads();

            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;

            handleInput();

            AlgorithmInfo ai = av[currentAlgorithm]->step(v);
            vis.draw(v, ai, av[currentAlgorithm]->name());
        }
    }

private:
    std::random_device rd;
    std::uniform_int_distribution<int> d;
    std::vector<int> v;
    std::vector<std::unique_ptr<Algorithm>> av;
    unsigned int currentAlgorithm = 0;
    int currentAmount = 0;
    Visualizer vis;

    void randomize(int amount) {
        v.clear();
        v.reserve(amount);

        for (int i = 0; i < amount; i++) {
            v.push_back(d(rd));
        }
    }

    void handleInput() {
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_RIGHT) {
            av[currentAlgorithm]->reset();
            if (currentAlgorithm++ >= av.size() - 1) currentAlgorithm = 0;
            randomize(currentAmount);
        }
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_LEFT) {
            av[currentAlgorithm]->reset();
            if (currentAlgorithm-- <= 0) currentAlgorithm = av.size() - 1;
            randomize(currentAmount);
        }

        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_UP && currentAmount < (WIDTH / 2)) {
            currentAmount += 5;
            randomize(currentAmount);
            av[currentAlgorithm]->reset();
        }
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_DOWN && currentAmount > 5) {
            currentAmount -= 5;
            randomize(currentAmount);
            av[currentAlgorithm]->reset();
        }
    }

};
