/**
 * Created by Aliaksei Tokarau on 4/1/2020.
 * plik: max_heap.cpp
 * zawartosc: implementacja metod zadeklarowanych w max_heap.h
 */

#include "max_heap.h"


bool max_heap::insert(int value) {
    if (this->size == MAX_SIZE) {
        return false;
    }

    this->size++;
    int index = this->size - 1;
    this->arr[index] = value;

    shift_up(index);
    return true;
}


void max_heap::shift_up(int index) {
    if (index > this->size || index == 0) {
        return;
    }

    if (this->arr[index] > this->arr[parent(index)]) {
        swap(&this->arr[parent(index)], &this->arr[index]);
    }

    shift_up(parent(index));
}


void max_heap::shift_down(int index) {
    if (index > this->size) {
        return;
    }

    int swap_index = index;

    if (left(index) <= this->size && this->arr[index] < this->arr[left(index)]) {
        swap_index = left(index);
    }

    if (right(index) <= this->size && this->arr[swap_index] < this->arr[right(index)]) {
        swap_index = right(index);
    }

    if (swap_index != index) {
        swap(&this->arr[index], &this->arr[swap_index]);
        shift_down(swap_index);
    }
}


bool max_heap::remove(int value) {
    int index = this->find(value);

    if (index == -1) {
        return false;
    }

    this->size--;
    swap(&this->arr[index], &this->arr[size]);
    this->arr[size] = 0;
    this->shift_down(index);

    return true;
}


int max_heap::find(int value) {
    for (int i = 0; i < this->size; i++) {
        if (this->arr[i] == value) {
            return i;
        }
    }

    return -1;
}


void max_heap::print_horiz() {
    std::cout << "Struct: max heap" << std::endl;
    std::cout << "Size: " << this->size << std::endl;
    std::cout << "Heap array: " << this->to_string() << std::endl;
    std::cout << "Tree form: " << std::endl;

    int heap_depth = floor(log2(this->size)) + 1;
    int depth_count = heap_depth;

    int sign_num = 0;
    int max_num = this->arr[0];
    while (max_num != 0) {
        max_num /= 10;
        sign_num++;
    }

    int edge_space_int = pow(2, (depth_count - 1)) - 1;
    int node_space_int = pow(2, (depth_count - 1)) - 1;

    std::string default_space;
    for (int i = 0; i < sign_num; i++) {
        default_space.push_back(' ');
    }

    std::string edge_space;
    for (int i = 0; i < edge_space_int; i++) {
        edge_space.append(default_space);
    }

    std::string node_space;
    for (int i = 0; i < node_space_int; i++) {
        node_space.append(default_space);
    }

    int curr_point = 0;
    for (int curr_depth = 0; curr_depth < heap_depth; curr_depth++) {
        std::cout << edge_space;

        int counter = pow(2, curr_depth);
        for (int i = 0; i < counter; i++) {
            if (i + curr_point == this->size) {
                std::cout << std::endl;
                return;
            }

            std::cout << std::setfill('0') << std::setw(sign_num) << this->arr[i + curr_point];
            std::cout << node_space;
        }
        curr_point += counter;

        std::cout << std::endl;

        node_space_int = pow(2, (depth_count - 1)) - 1;
        depth_count--;
        edge_space_int = pow(2, (depth_count - 1)) - 1;

        node_space.clear();
        for (int i = 0; i < node_space_int; i++) {
            node_space.append(default_space);
        }

        edge_space.clear();
        for (int i = 0; i < edge_space_int; i++) {
            edge_space.append(default_space);
        }
    }
}


std::string max_heap::to_string() {
    std::string str_arr;
    str_arr.append("{ ");

    if (this->size > 0) {
        str_arr.append(std::to_string(this->arr[0]));
    }

    for (int i = 1; i < this->size; i++) {
        str_arr.append(", ");
        str_arr.append(std::to_string(this->arr[i]));
    }

    str_arr.append(" }");
    return str_arr;
}


void max_heap::clear() {
    for (int i = 0; i < this->size; i++) {
        this->arr[i] = 0;
    }

    this->size = 0;
}


bool max_heap::load_from_file(const std::string &file_name) {
    std::fstream file(file_name);

    if (!file) {
        return false;
    }

    int init_size;
    file >> init_size;

    if (init_size > MAX_SIZE) {
        return false;
    }

    this->clear();
    for (int i = 0; i < init_size; i++) {
        int element;
        file >> element;
        this->insert(element);
    }

    file.close();
    return true;
}


bool max_heap::generate(int init_size) {
    if (init_size > MAX_SIZE) {
        return false;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(INT16_MIN, INT16_MAX);

    this->clear();
    for (int i = 0; i < init_size; i++) {
        this->insert(dist(mt));
    }

    return true;
}


void max_heap::print_vert(std::string sp, std::string sn, int index, bool launch) {
    if (index == 0 && !launch) {
        return;
    }

    std::string cr, cl, cp;
    cr = cl = cp = "  ";
    cr[0] = 218;
    cr[1] = 196;
    cl[0] = 192;
    cl[1] = 196;
    cp[0] = 179;

    std::string s;
    if (index < this->size) {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        print_vert(s + cp, cr, right(index), false);

        s = s.substr(0, sp.length() - 2);
        std::cout << s << sn << this->arr[index] << std::endl;

        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        print_vert(s + cp, cl, left(index), false);
    }
}

void max_heap::print() {
    std::cout << "Struct: max heap" << std::endl;
    std::cout << "Size: " << this->size << std::endl;
    std::cout << "Heap array: " << this->to_string() << std::endl;
    std::cout << "Tree form: " << std::endl;

    this->print_vert("", "", 0, true);
}


