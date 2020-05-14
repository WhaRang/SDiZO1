//
// Created by aleks on 3/29/2020.
//

#include "linked_list.h"

linked_list::linked_list() {
    this->head = nullptr;
    this->size = 0;
}


void linked_list::push_back(int e) {
    node *temp_node = new node;
    temp_node->value = e;

    if (size == 0) {
        this->head = temp_node;
        this->head->next = nullptr;
        this->head->prev = nullptr;
        this->size++;
        return;
    }

    if (size == 1) {
        this->tail = temp_node;
        this->tail->prev = this->head;
        this->tail->next = nullptr;
        this->head->next = this->tail;
        this->head->prev = nullptr;
        this->size++;
        return;
    }

    temp_node->prev = this->tail;
    this->tail->next = temp_node;
    this->tail = temp_node;
    this->tail->next = nullptr;
    this->size++;
}


void linked_list::push_front(int e) {
    node *temp_node = new node;
    temp_node->value = e;

    if (this->size == 0) {
        this->head = temp_node;
        this->head->next = nullptr;
        this->head->prev = nullptr;
        this->size++;
        return;
    }

    if (this->size == 1) {
        this->tail = this->head;
        this->head = temp_node;
        this->head->prev = nullptr;
        this->head->next = this->tail;
        this->tail->prev = this->head;
        this->tail->next = nullptr;
        this->size++;
        return;
    }

    temp_node->next = this->head;
    this->head->prev = temp_node;
    this->head = temp_node;
    this->head->prev = nullptr;
    this->size++;
}


bool linked_list::add(int index, int value) {
    if (this->size < index || index < 0) {
        return false;
    }

    if (index == 0) {
        this->push_front(value);
        return true;
    }

    if (index >= size) {
        this->push_back(value);
        return true;
    }

    node *temp_node = new node;
    temp_node->value = value;

    node *curr_node;
    curr_node = this->head;

    for (int i = 0; i < index; i++) {
        curr_node = curr_node->next;
    }

    node *prev_node = curr_node->prev;

    temp_node->next = curr_node;
    curr_node->prev = temp_node;

    temp_node->prev = prev_node;
    prev_node->next = temp_node;
    this->size++;

    return true;
}


void linked_list::add_rand() {
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


void linked_list::remove_last() {
    if (size == 0) {
        return;
    }

    if (size == 1) {
        delete this->head;
        this->head = nullptr;
        this->size--;
        return;
    }

    node *prev_node = this->tail->prev;
    prev_node->next = nullptr;
    delete this->tail;
    this->tail = prev_node;
    this->size--;
}


void linked_list::remove_first() {
    if (size <= 1) {
        return this->remove_last();
    }

    if (size == 2) {
        this->tail = this->head;
    }

    node *next_node = this->head->next;
    next_node->prev = nullptr;
    delete this->head;
    this->head = next_node;
    this->size--;
}


bool linked_list::remove(int value) {
    int index = this->find(value);

    if (this->size == 0 || index == -1) {
        return false;
    }

    if (index == 0) {
        this->remove_first();
        return true;
    }

    if (index == size - 1) {
        this->remove_last();
        return true;
    }

    node *curr_node = this->head;
    for (int i = 0; i < this->size; i++) {
        if (curr_node->value == value) {
            node *next_node = curr_node->next;
            node *prev_node = curr_node->prev;

            prev_node->next = next_node;
            next_node->prev = prev_node;

            delete curr_node;
            this->size--;
            return true;
        }
        if (curr_node->next) {
            curr_node = curr_node->next;
        }
    }

    return true;
}


void linked_list::remove_rand() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distSIZE(0, this->size - 1);

    this->remove(distSIZE(mt));
}


void linked_list::print() {
    std::cout << "Struct: linked list" << std::endl;
    std::cout << "Size: " << this->size << std::endl;
    std::cout << "Normal order: " << this->to_string() << std::endl;
    std::cout << "Reversed order: " << this->reversed_to_string() << std::endl;
}


void linked_list::generate(int init_size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(INT16_MIN, INT16_MAX);

    this->clear();
    for (int i = 0; i < init_size; i++) {
        this->push_back(dist(mt));
    }
}


void linked_list::clear() {
    int counter = this->size;

    for (int i = 0; i < counter; i++) {
        this->remove_first();
    }
}


int linked_list::find(int value) {
    int counter = 0;

    node *curr_node;
    curr_node = this->head;

    while (curr_node != nullptr) {
        if (curr_node->value == value) {
            return counter;
        }
        curr_node = curr_node->next;
        counter++;
    }

    return -1;
}


bool linked_list::load_from_file(const std::string &file_name) {
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


std::string linked_list::to_string() {
    std::string str_list;
    str_list.append("{ ");

    node *curr_node = head;

    if (this->size > 0) {
        str_list.append(std::to_string(curr_node->value));
    }

    if (curr_node != nullptr) {
        while (curr_node->next != nullptr) {
            curr_node = curr_node->next;
            str_list.append(", ");
            str_list.append(std::to_string(curr_node->value));
        }
    }

    str_list.append(" }");
    return str_list;
}

int linked_list::get_size() {
    return this->size;
}

std::string linked_list::reversed_to_string() {
    std::string str_list;
    str_list.append("{ ");

    if (this->size <= 1) {
        return this->to_string();
    }

    node *curr_node = tail;

    if (this->size > 0) {
        str_list.append(std::to_string(curr_node->value));
    }

    if (curr_node != nullptr) {
        while (curr_node->prev != nullptr) {
            curr_node = curr_node->prev;
            str_list.append(", ");
            str_list.append(std::to_string(curr_node->value));
        }
    }

    str_list.append(" }");
    return str_list;
}

