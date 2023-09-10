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
    
    virtual std::string name() const = 0;
};

class BubbleSort : public Algorithm {
public:
    BubbleSort(std::vector<int>& arr) : v(arr) {}

    // Implement the sort method for bubble sort
    bool step(std::vector<int>& arr) override {
        if (i < arr.size() - 1) {
            if (j < arr.size() - i - 1) {
                if (arr[j] > arr[j + 1]) { // Use '>' for ascending order
                    std::swap(arr[j], arr[j + 1]);
                }
                j++;
            } else {
                // Move to the next pass of the algorithm
                i++;
                j = 0;
            }
            return true; // Indicate that a step was performed
        }
        return false; // Sorting is complete
    }

    void reset() override {
        i = 0;
        j = 0;
    }

    std::string name() const override {
        return "Bubble Sort";
    }

private:
    std::vector<int>& v;
    unsigned int i = 0;
    unsigned int j = 0;
};
