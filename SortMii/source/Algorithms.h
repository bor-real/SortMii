#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "AlgorithmInfo.h"

class Algorithm {
public:
    virtual AlgorithmInfo step(std::vector<int>& arr) = 0;
    virtual void reset() = 0;
    virtual std::string name() const = 0;
};

class BubbleSort : public Algorithm {
public:
    BubbleSort(std::vector<int>& arr) : v(arr) {}

    AlgorithmInfo step(std::vector<int>& arr) override {
        AlgorithmInfo info;

        if (i < arr.size() - 1) {
            if (j < arr.size() - i - 1) {
                accesses += 2;
                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
                j++;
            } else {
                i++;
                j = 0;
            }
        }

        info.redPos = j;
        info.accesses = accesses;
        info.comparisons = comparisons;

        return info;
    }

    void reset() override {
        i = 0;
        j = 0;
        comparisons = 0;
        accesses = 0;
    }

    std::string name() const override {
        return "Bubble Sort";
    }

private:
    std::vector<int>& v;
    unsigned int i = 0;
    unsigned int j = 0;
    int comparisons = 0;
    int accesses = 0;
};

class CocktailShakerSort : public Algorithm {
public:
    CocktailShakerSort(std::vector<int>& arr) : v(arr) {}

    AlgorithmInfo step(std::vector<int>& arr) override {
        AlgorithmInfo info;

        if (i < arr.size() - 1) {
            if (direction == 0) {  // Moving right
                if (j < arr.size() - i - 1) {
                    accesses += 2;
                    comparisons++;
                    if (arr[j] > arr[j + 1]) {
                        std::swap(arr[j], arr[j + 1]);
                    }
                    j++;
                } else {
                    direction = 1;  // Change direction to move left
                    j = arr.size() - i - 1;
                }
            } else {  // Moving left
                if (j > i) {
                    accesses += 2;
                    comparisons++;
                    if (arr[j] < arr[j - 1]) {
                        std::swap(arr[j], arr[j - 1]);
                    }
                    j--;
                } else {
                    i++;
                    direction = 0;  // Change direction to move right
                    j = i;
                }
            }
        }

        info.redPos = j;
        info.bluePos = 0;
        info.accesses = accesses;
        info.comparisons = comparisons;

        return info;
    }

    void reset() override {
        i = 0;
        j = 0;
        direction = 0;  // Start by moving right
        comparisons = 0;
        accesses = 0;
    }

    std::string name() const override {
        return "Cocktail Sort"; // it would cut off if i included shaker
    }

private:
    std::vector<int>& v;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int direction = 0;  // 0 for right, 1 for left
    int comparisons = 0;
    int accesses = 0;
};


class GnomeSort : public Algorithm {
public:
    GnomeSort(std::vector<int>& arr) : v(arr) {}

    AlgorithmInfo step(std::vector<int>& arr) override {
        AlgorithmInfo info;

        if (pos == 0) {
            pos++;
        }
        if (pos < arr.size()) {

            if (arr[pos] >= arr[pos - 1]) {
                pos++;
            } else {
                std::swap(arr[pos], arr[pos - 1]);
                pos--;
            }

            info.redPos = pos;
            accesses += 2;
            comparisons++;
        } else {
            info.redPos = 0;
            info.bluePos = 0;
        }

        info.accesses = accesses;
        info.comparisons = comparisons;

        return info;
    }

    void reset() override {
        pos = 0;
        accesses = 0;
        comparisons = 0;
    }

    std::string name() const override {
        return "Gnome Sort";
    }

private:
    std::vector<int>& v;
    unsigned int pos = 0;
    int accesses = 0;
    int comparisons = 0;
};

class InsertionSort : public Algorithm {
public:
    InsertionSort(std::vector<int>& arr) : v(arr) {}

    AlgorithmInfo step(std::vector<int>& arr) override {
        AlgorithmInfo info;

        if (i < arr.size()) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                comparisons++;
                accesses += 2;
            }

            arr[j + 1] = key;
            i++;
            accesses += 2;

            info.redPos = i;
            info.bluePos = j + 1; 
        } else {
            info.redPos = 0;
            info.bluePos = 0;
        }

        info.accesses = accesses;
        info.comparisons = comparisons;

        return info;
    }


    void reset() override {
        i = 1;
        accesses = 0;
        comparisons = 0;
    }

    std::string name() const override {
        return "Insertion Sort";
    }

private:
    std::vector<int>& v;
    unsigned int i = 1;
    int accesses = 0;
    int comparisons = 0;
};
