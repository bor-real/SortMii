#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include <iostream>
#include <vector>
#include <string>

class Algorithm  {
public:
    virtual bool step(std::vector<int>& arr) = 0;
    virtual void reset() = 0;
    virtual std::string name() = 0;
private: 
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

    std::string name() override {
        return "Bubble Sort";
    }

private:
    std::vector<int>& v;
    unsigned int i = 0;
    unsigned int j = 0;
};

class GnomeSort : public Algorithm {
public:
    GnomeSort(std::vector<int>& arr) : v(arr) {}

    bool step(std::vector<int>& arr) override {
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
            return true;
        }
        return false;
    }

    void reset() override {
        pos = 0;
    }

    std::string name() override {
        return "Gnome Sort";
    }

private:
    std::vector<int>& v;
    unsigned int pos = 0;
};

class InsertionSort : public Algorithm {
public:
    InsertionSort(std::vector<int>& arr) : v(arr) {}

    bool step(std::vector<int>& arr) override {
        if (i < arr.size()) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }

            arr[j + 1] = key;
            i++;
            return true;
        }
        return false;
    }

    void reset() override {
        i = 1;
    }

    std::string name() override {
        return "Insertion Sort";
    }

private:
    std::vector<int>& v;
    unsigned int i = 1;
};
