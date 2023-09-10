#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include <iostream>
#include <vector>
#include <string>

class Algorithm {
public:
    virtual bool step(std::vector<int>& arr) = 0;
    virtual void reset() = 0;
};

class BubbleSort : public Algorithm {
public:
    BubbleSort(std::vector<int>& arr) : v(arr) {}

    bool step(std::vector<int>& arr) override {
        if (i < arr.size() - 1) {
            if (j < arr.size() - i - 1) {
                if (arr[j] > arr[j + 1]) { // > is ascending
                    std::swap(arr[j], arr[j + 1]);
                }
                j++;
            } else {
                i++;
                j = 0;
            }
            return true;
        }
        return false;
    }

    void reset() override {
        i = 0;
        j = 0;
    }

private:
    std::vector<int>& v;
    unsigned int i = 0;
    unsigned int j = 0;
};
