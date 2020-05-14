//
// Created by aleks on 3/29/2020.
//

#ifndef SDIZO_PROJECT_LINKED_LIST_H
#define SDIZO_PROJECT_LINKED_LIST_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <random>

struct node {
    int value;
    node *next;
    node *prev;
};

class linked_list {

public:

    linked_list();

    void push_back(int e);

    void push_front(int e);

    bool add(int index, int value);

    void add_rand();

    void remove_last();

    void remove_first();

    bool remove(int value);

    void remove_rand();

    void generate(int init_size);

    void clear();

    int find(int value);

    bool load_from_file(const std::string &file_name);

    void print();

    int get_size();

    std::string to_string();

    std::string reversed_to_string();

private:
    node *head;
    node *tail;

    int size;
};


#endif //SDIZO_PROJECT_LINKED_LIST_H
