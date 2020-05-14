/**
 * Created by Aliaksei Tokarau on 4/1/2020.
 * plik: max_heap.cpp
 * zawartosc: deklaracja metod klasy rb_tree
 */

#ifndef SDIZO_PROJECT_RB_TREE_H
#define SDIZO_PROJECT_RB_TREE_H

#include <string>
#include <iostream>
#include <cassert>
#include <random>
#include <fstream>

class rb_tree {

    enum NodeColor {
        BLACK,
        RED
    };

public:

    struct Node {
        int data;
        Node *parent;
        NodeColor color;
        Node *left;
        Node *right;

        explicit Node(int data) {
            this->data = data;
            left = right = parent = nullptr;
            this->color = RED;
        }
    };

    rb_tree();

    void insert(int data);

    bool remove_key(int key);

    void remove_node(Node *node);

    Node *find(int key);

    void print();

    void clear();

    void generate(int init_size);

    bool load_from_file(std::string file_name);

protected :

    Node *get_parent(Node *node);

    Node *get_grand_parent(Node *node);

    Node *get_sibling(Node *node);

    Node *get_uncle(Node *node);

    void left_rotation(Node *n);

    void right_rotation(Node *node);

    void insert_Recurse(Node *root, Node *node);

    Node *find_Recurse(int key, Node *node);

    void fix_violation(Node *node);

    void replace(Node* node, Node* child);

    void remove_case1(Node *node);

    void remove_case2(Node *node);

    void remove_case3(Node *node);

    void remove_case4(Node *node);

    void remove_case5(Node *node);

    void remove_case6(Node *node);

    Node *successor(Node *node);

    void clear_Recurse(Node *node);

    void print(std::string sp, std::string sn, Node *node, bool launch);

private:

    Node *root;

};


#endif //SDIZO_PROJECT_RB_TREE_H
