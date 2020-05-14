cmake_minimum_required(VERSION 3.15)
project(SDiZO_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDiZO_project main.cpp menu.cpp menu.h menu_element.cpp menu.h
        resources.h array.h array.cpp linked_list.h linked_list.cpp max_heap.cpp
        max_heap.h test.cpp rb_tree.cpp rb_tree.h)