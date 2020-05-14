
/**
 * Created by Aliaksei Tokarau on 3/17/2020.
 * plik: main.cpp
 * zawartosc: applikacja konsolowa do testowania operacji na roznych strukturach danych
 */


#include <iostream>

#include "rb_tree.h"
#include "menu.h"
#include "array.h"
#include "linked_list.h"
#include "max_heap.h"
#include <chrono>

void am_foo();

void llm_foo();

void mhm_foo();

void rbtm_foo();

void exit_foo();

void load_from_file();

void delete_element();

void add_element();

void find_element();

void generate();

void print_dialogue();

void print();

void test();

void dialogue_message(const std::string &message);


enum StructType {
    ARRAY,
    LINKED_LIST,
    MAX_HEAP,
    RED_BLACK_TREE
};

enum Operation {
    PUSH_BACK,
    PUSH_FRONT,
    REMOVE_LAST,
    REMOVE_FIRST,
    ADD_RAND,
    REMOVE_RAND,
    FIND
};


void test_arr(int size, int cache, int repeats, Operation o);

void test_list(int size, int cache, int repeats, Operation o);

void test_heap(int size, int cache, int repeats, Operation o);

void test_tree(int size, int cache, int repeats, Operation o);

std::string get_operation_str(Operation o);

std::string get_struct_str(StructType type);

array arr;
linked_list list;
max_heap heap;
rb_tree tree;

StructType curr_struct;

menu_element am_me("-- Array          --", am_foo);
menu_element llm_me("-- Linked List    --", llm_foo);
menu_element mhm_me("-- Max Heap       --", mhm_foo);
menu_element rbtm_me("-- Red-black Tree --", rbtm_foo);
menu_element exit_me("-- Exit           --", exit_foo);
menu main_menu({am_me, llm_me, mhm_me, rbtm_me, exit_me});

menu_element lff_me("-- Load From File --", load_from_file);
menu_element del_me("-- Delete Element --", delete_element);
menu_element add_me("-- Add Element    --", add_element);
menu_element fnd_me("-- Find Element   --", find_element);
menu_element gen_me("-- Generate New   --", generate);
menu_element prt_me("-- Print          --", print_dialogue);
menu_element tst_me("-- Run Test       --", test);
menu_element bck_me("-- Back           --");

menu array_menu({lff_me, del_me, add_me, fnd_me, gen_me, prt_me, tst_me, bck_me});
menu list_menu({lff_me, del_me, add_me, fnd_me, gen_me, prt_me, tst_me, bck_me});
menu heap_menu({lff_me, del_me, add_me, fnd_me, gen_me, prt_me, tst_me, bck_me});
menu tree_menu({lff_me, del_me, add_me, fnd_me, gen_me, prt_me, tst_me, bck_me});


int main() {
    dialogue_message("Use ARROW keys and ENTER or ESC to navigate in program.");
    main_menu.run();
    return 0;
}


void test() {
    int init_size = 25000, init_cache = 1000;
    int repeats = 100;

    switch (curr_struct) {
        case ARRAY: {
            for (int o = 0; o < 8; o++) {
                int curr_size = init_size;
                std::cout << "-------------------------------------------------------" << std::endl;
                for (int j = 1; j < 8; j++) {
                    test_arr(curr_size, init_cache, repeats, static_cast<Operation>(o));
                    curr_size *= 2;
                }
                std::cout << "-------------------------------------------------------" << std::endl;
            }
            break;
        }

        case LINKED_LIST: {
            for (int o = 0; o < 8; o++) {
                int curr_size = init_size;
                std::cout << "-------------------------------------------------------" << std::endl;
                for (int i = 1; i < 8; i++) {
                    test_list(curr_size, init_cache, repeats, static_cast<Operation>(o));
                    curr_size *= 2;
                }
                std::cout << "-------------------------------------------------------" << std::endl;
            }
            break;
        }

        case MAX_HEAP: {
            for (int o = 5; o < 8; o++) {
                int curr_size = init_size;
                std::cout << "-------------------------------------------------------" << std::endl;
                for (int i = 1; i < 8; i++) {
                    test_heap(curr_size, init_cache, repeats, static_cast<Operation>(o));
                    curr_size *= 2;
                }
                std::cout << "-------------------------------------------------------" << std::endl;
            }
            break;
        }

        case RED_BLACK_TREE: {
            for (int o = 5; o < 8; o++) {
                int curr_size = init_size;
                std::cout << "-------------------------------------------------------" << std::endl;
                for (int i = 1; i < 8; i++) {
                    test_heap(curr_size, init_cache, repeats, static_cast<Operation>(o));
                    curr_size *= 2;
                }
                std::cout << "-------------------------------------------------------" << std::endl;
            }
            break;
        }

    }
    dialogue_message("Done.");
}

void test_tree(int size, int cache, int repeats, Operation o) {
    double sum = 0;

    for (int i = 0; i < repeats; i++) {
        tree.generate(size);
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < cache; j++) {
            switch (o) {
                case ADD_RAND: {
                    tree.insert(size / 2 + i);
                    break;
                }
                case REMOVE_RAND: {
                    tree.remove_key(j);
                    break;
                }
                case FIND: {
                    tree.find(size / 2 + j);
                    break;
                }
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    }
    std::cout << "Size: " << size << ", cache: " << cache
              << ", operation: " << get_operation_str(o) << ", result(nanoseconds): "
              << std::setprecision(15) << sum / repeats << std::endl;
}


void test_heap(int size, int cache, int repeats, Operation o) {
    double sum = 0;

    for (int i = 0; i < repeats; i++) {
        heap.generate(size);
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < cache; j++) {
            switch (o) {
                case ADD_RAND: {
                    heap.insert(size / 2 + i);
                    break;
                }
                case REMOVE_RAND: {
                    heap.remove(j);
                    break;
                }
                case FIND: {
                    heap.find(size / 2 + j);
                    break;
                }
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    }
    std::cout << "Size: " << size << ", cache: " << cache
              << ", operation: " << get_operation_str(o) << ", result(nanoseconds): "
              << std::setprecision(15) << sum / repeats << std::endl;
}


void test_list(int size, int cache, int repeats, Operation o) {
    double sum = 0;

    for (int i = 0; i < repeats; i++) {
        list.generate(size);
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < cache; j++) {
            switch (o) {
                case PUSH_BACK: {
                    list.push_back(j);
                    break;
                }
                case PUSH_FRONT: {
                    list.push_front(j);
                    break;
                }
                case ADD_RAND: {
                    list.add(size / 2, cache);
                    break;
                }
                case REMOVE_FIRST: {
                    list.remove_first();
                    break;
                }
                case REMOVE_LAST: {
                    list.remove_last();
                    break;
                }
                case REMOVE_RAND: {
                    list.remove(j);
                    break;
                }
                case FIND: {
                    list.find(size / 2 + j);
                    break;
                }
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    }
    std::cout << "Size: " << size << ", cache: " << cache
              << ", operation: " << get_operation_str(o) << ", result(nanoseconds): "
              << std::setprecision(15) << sum / repeats << std::endl;
}


void test_arr(int size, int cache, int repeats, Operation o) {
    double sum = 0;

    arr.generate(size);
    for (int i = 0; i < repeats; i++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < cache; j++) {
            switch (o) {
                case PUSH_BACK: {
                    arr.push_back(j);
                    break;
                }
                case PUSH_FRONT: {
                    arr.push_front(j);
                    break;
                }
                case ADD_RAND: {
                    arr.add(size / 2, cache);
                    break;

                }
                case REMOVE_FIRST: {
                    arr.pop_front();
                    break;
                }

                case REMOVE_LAST: {
                    arr.pop_back();
                    break;
                }
                case REMOVE_RAND: {
                    arr.remove(j);
                    break;
                }
                case FIND: {
                    arr.find(size / 2 + j);
                    break;
                }
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        sum += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    std::cout << "Size: " << size << ", cache: " << cache
              << ", operation: " << get_operation_str(o) << ", result(microseconds): "
              << std::setprecision(15) << sum / repeats << std::endl;
}


void find_element() {
    int value;
    std::cout << "Enter value of element to find: ";
    std::cin >> value;

    int pos = -1;
    bool in_tree = false;

    switch (curr_struct) {
        case ARRAY: {
            pos = arr.find(value);
            break;
        }

        case LINKED_LIST: {
            pos = list.find(value);
            break;
        }

        case MAX_HEAP: {
            pos = heap.find(value);
            break;
        }

        case RED_BLACK_TREE: {
            in_tree = tree.find(value);
            break;
        }
    }

    print();

    if (in_tree) {
        dialogue_message("Found element with value " + std::to_string(value)
                         + " in " + get_struct_str(curr_struct) + ".\n");
        return;
    }

    if (pos == -1) {
        dialogue_message("There is no " + std::to_string(value)
                         + " in " + get_struct_str(curr_struct));
    } else {
        dialogue_message("Found element with value " + std::to_string(value)
                         + " in " + get_struct_str(curr_struct) + ".\n"
                         + "First occurrence on position: " + std::to_string(pos));
    }
}


void print_dialogue() {
    print();
    dialogue_message("");
}


void print() {
    switch (curr_struct) {
        case ARRAY: {
            arr.print();
            break;
        }

        case LINKED_LIST: {
            list.print();
            break;
        }

        case MAX_HEAP: {
            heap.print();
            break;
        }

        case RED_BLACK_TREE: {
            tree.print();
            break;
        }
    }
}


void generate() {
    int init_size;
    std::cout << "Enter size of new " << get_struct_str(curr_struct) << ": ";
    std::cin >> init_size;

    bool is_generated = true;

    switch (curr_struct) {
        case ARRAY: {
            arr.generate(init_size);
            break;
        }

        case LINKED_LIST: {
            list.generate(init_size);
            break;
        }

        case MAX_HEAP: {
            is_generated = heap.generate(init_size);
            break;
        }

        case RED_BLACK_TREE: {
            tree.generate(init_size);
            break;
        }
    }

    print();

    if (is_generated) {
        dialogue_message("Generated new " + get_struct_str(curr_struct)
                         + " with size " + std::to_string(init_size));
    } else {
        dialogue_message("Error generating new " + get_struct_str(curr_struct));
    }
}


void add_element() {
    bool is_added = false;

    switch (curr_struct) {
        case ARRAY: {
            int index;
            int value;

            std::cout << "Enter index of element to add: ";
            std::cin >> index;
            std::cout << "Enter value of element to add: ";
            std::cin >> value;

            is_added = arr.add(index, value);
            break;
        }

        case LINKED_LIST: {
            int index;
            int value;

            std::cout << "Enter index of element to add: ";
            std::cin >> index;
            std::cout << "Enter value of element to add: ";
            std::cin >> value;

            is_added = list.add(index, value);
            break;
        }

        case MAX_HEAP: {
            int key;
            std::cout << "Enter key of element to insert: ";
            std::cin >> key;

            is_added = heap.insert(key);
            break;
        }

        case RED_BLACK_TREE: {
            int key;
            std::cout << "Enter key of element to insert: ";
            std::cin >> key;

            tree.insert(key);
            is_added = true;
            break;
        }
    }

    print();

    if (is_added) {
        dialogue_message("Element was added correctly");
    } else {
        dialogue_message("Error adding element");
    }
}


void delete_element() {
    boolean is_deleted = false;

    switch (curr_struct) {
        case ARRAY: {
            int index;
            std::cout << "Enter index of element to delete: ";
            std::cin >> index;

            is_deleted = arr.remove(index);
            break;
        }

        case LINKED_LIST: {
            int value;
            std::cout << "Enter value of element to delete: ";
            std::cin >> value;

            is_deleted = list.remove(value);
            break;
        }

        case MAX_HEAP: {
            int key;
            std::cout << "Enter key of element to delete: ";
            std::cin >> key;

            is_deleted = heap.remove(key);
            break;
        }

        case RED_BLACK_TREE: {
            int key;
            std::cout << "Enter key of element to delete: ";
            std::cin >> key;

            is_deleted = tree.remove_key(key);
            break;
        }
    }

    print();

    if (is_deleted ) {
        dialogue_message("Element was deleted correctly");
    } else {
        dialogue_message("Error deleting element");
    }
}


void load_from_file() {
    std::string file_name;
    std::cout << "Enter file name: ";
    std::cin >> file_name;

    bool is_loaded = false;

    switch (curr_struct) {
        case ARRAY: {
            is_loaded = arr.load_from_file(file_name);
            break;
        }

        case LINKED_LIST: {
            is_loaded = list.load_from_file(file_name);
            break;
        }

        case MAX_HEAP: {
            is_loaded = heap.load_from_file(file_name);
            break;
        }

        case RED_BLACK_TREE: {
            is_loaded = tree.load_from_file(file_name);
            break;
        }
    }

    print();

    if (is_loaded) {
        dialogue_message("Correctly loaded from file");
    } else {
        dialogue_message("Error loading from file");
    }
}


void am_foo() {
    curr_struct = ARRAY;
    array_menu.run();
}

void llm_foo() {
    curr_struct = LINKED_LIST;
    list_menu.run();
}

void mhm_foo() {
    curr_struct = MAX_HEAP;
    heap_menu.run();
}

void rbtm_foo() {
    curr_struct = RED_BLACK_TREE;
    tree_menu.run();
}

void exit_foo() {
    exit(1);
}


void dialogue_message(const std::string &message) {
    std::cout << message << std::endl <<
              "press ENTER to continue...";
    int key = 1;
    while (key != Keys::ENTER) {
        key = _getch();
    }
}


std::string get_operation_str(Operation o) {
    switch (o) {
        case PUSH_BACK: {
            return "adding element on last position";
        }
        case PUSH_FRONT: {
            return "adding element on first position";
        }
        case ADD_RAND: {
            return "adding element on random position";
        }
        case REMOVE_LAST: {
            return "removing last element";
        }
        case
            REMOVE_FIRST: {
            return "removing first element";
        }
        case REMOVE_RAND: {
            return "removing random element";
        }
        case FIND: {
            return "searching for element";
        }
    }
}


std::string get_struct_str(StructType type) {
    switch (type) {
        case ARRAY: {
            return "array";
        }
        case LINKED_LIST: {
            return "linked list";
        }
        case MAX_HEAP: {
            return "max heap";
        }
        case RED_BLACK_TREE: {
            return "red-black tree";
        }
    }
}