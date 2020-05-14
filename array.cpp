/**
 * Created by Aliaksei Tokarau on 3/17/2020.
 * plik: array.cpp
 * zawartosc: implementacja metod zadeklarowanych w array.h
 */

#include "array.h"


array::array() {
    this->size = 0;
    this->arr = new int[this->size];
}


void array::print() {
    std::cout << "Struct: array" << std::endl;
    std::cout << "Size: " << this->size << std::endl;
    std::cout << this->to_string() << std::endl;
}


void array::push_back(int e) {
    int *old_arr = this->arr;
    this->size++;
    int *new_arr = new int[this->size];
    for (int i = 0; i < this->size - 1; i++) {
        new_arr[i] = old_arr[i];
    }

    delete[] old_arr;
    this->arr = new_arr;
    this->arr[this->size - 1] = e;
}


void array::push_front(int e) {
    int *old_arr = this->arr;
    this->size++;
    int *new_arr = new int[this->size];
    for (int i = 0; i < this->size - 1; i++) {
        new_arr[i + 1] = old_arr[i];
    }

    delete[] old_arr;
    this->arr = new_arr;
    arr[0] = e;
}


void array::pop_back() {
    if (this->size <= 0) {
        return;
    }

    int *old_arr = this->arr;
    this->size--;
    int *new_arr = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        new_arr[i] = old_arr[i];
    }

    delete[] old_arr;
    this->arr = new_arr;
}


void array::pop_front() {
    if (this->size <= 0) {
        return;
    }
    int *old_arr = this->arr;
    this->size--;
    int *new_arr = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        new_arr[i] = old_arr[i + 1];
    }

    delete[] old_arr;
    this->arr = new_arr;
}


bool array::remove(int index) {
    if (this->size <= index || this->size == 0) {
        return false;
    }

    int *old_arr = this->arr;
    this->size--;
    int *new_arr = new int[this->size];
    for (int i = 0; i < index; i++) {
        new_arr[i] = old_arr[i];
    }
    for (int i = index; i < this->size; i++) {
        new_arr[i] = old_arr[i + 1];
    }

    delete[] old_arr;
    this->arr = new_arr;
    return true;
}


void array::remove_rand() {
    if (this->size == 0) {
        return;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distSIZE(0, this->size - 1);

    this->remove(distSIZE(mt));
}


bool array::add(int index, int value) {
    if (this->size < index) {
        return false;
    }

    if (this-> size == index) {
        this->push_back(value);
        return true;
    }

    if (index == 0) {
        this->push_front(value);
        return true;
    }

    int *old_arr = this->arr;
    this->size++;
    int *new_arr = new int[this->size];
    for (int i = 0; i < index; i++) {
        new_arr[i] = old_arr[i];
    }
    new_arr[index] = value;
    for (int i = index + 1; i < size; i++) {
        new_arr[i] = old_arr[i - 1];
    }

    delete[] old_arr;
    this->arr = new_arr;
    return true;
}


void array::add_rand() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distINT16(INT16_MIN, INT16_MAX);
    std::uniform_real_distribution<double> distSIZE(0, this->size - 1);

    int value = distINT16(mt);
    if (this->size == 0) {
        this->push_back(value);
    } else {
        this->add(distSIZE(mt), distINT16(mt));
    }
}


void array::generate(unsigned int init_size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(INT16_MIN, INT16_MAX);

    this->clear();
    this->size = init_size;
    delete[] arr;
    this->arr = new int[size];
    for (int i = 0; i < init_size; i++) {
        this->arr[i] = dist(mt);
    }
}


unsigned int array::get_size() {
    return this->size;
}


bool array::load_from_file(const std::string &file_name) {
    std::fstream file(file_name);

    if (!file) {
        return false;
    }

    int init_size;
    file >> init_size;

    this->clear();
    for (int i = 0; i < init_size; i++) {
        int element;
        file >> element;
        this->push_back(element);
    }

    file.close();
    return true;
}


std::string array::to_string() {
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


void array::clear() {
    unsigned int counter = this->size;

    for (int i = 0; i < counter; i++) {
        this->pop_front();
    }
}


int array::find(int value) {
    for (int i = 0; i < this->size; i++) {
        if (arr[i] == value) {
            return i;
        }
    }

    return -1;
}
