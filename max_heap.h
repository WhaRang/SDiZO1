/**
 * Created by Aliaksei Tokarau on 4/1/2020.
 * plik: max_heap.h
 * zawartosc: deklaracja metod klasy max_heap
 */

#ifndef SDIZO_PROJECT_MAX_HEAP_H
#define SDIZO_PROJECT_MAX_HEAP_H

#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

class max_heap {

public:

    bool insert(int value);

    bool remove(int value);

    int find(int value);

    void shift_up(int index);

    void shift_down(int index);

    void print_horiz();

    void print_vert(std::string sp, std::string sn, int index, bool launch);

    void print();

    void clear();

    bool load_from_file(const std::string &file_name);

    bool generate(int init_size);

    std::string to_string();

private:
    int size = 0;
    const int MAX_SIZE = 200000;
    int *arr = new int[MAX_SIZE];

    static int parent(int i) { return (i - 1) / 2; };

    static int left(int i) { return (2 * i + 1); };

    static int right(int i) { return (2 * i + 2); };

    static int sibling(int i) {
        int p_index = parent(i);
        if (i == left(p_index)) {
            return right(p_index);
        } else {
            return left(p_index);
        }
    };

    static void swap(int *x, int *y) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }
};


#endif //SDIZO_PROJECT_MAX_HEAP_H
