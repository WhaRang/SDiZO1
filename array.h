/**
 * Created by Aliaksei Tokarau on 3/17/2020.
 * plik: array.h
 * zawartosc: deklaracja metod klasy @array
 */

#ifndef SDIZO_PROJECT_ARRAY_H
#define SDIZO_PROJECT_ARRAY_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <random>

class array {
public:
    explicit array();

    void push_back(int e);

    void push_front(int e);

    bool add(int index, int value);

    void add_rand();

    void pop_back();

    void pop_front();

    bool remove(int index);

    void remove_rand();

    void generate(unsigned int init_size);

    bool load_from_file(const std::string &file_name);

    int find(int value);

    void print();

    void clear();

    std::string to_string();

    unsigned int get_size();

private:
    unsigned int size;
    int *arr;
};


#endif //SDIZO_PROJECT_ARRAY_H
