#pragma once
#include "figures.h"

class Array
{
public:
    Array();
    void resize(size_t new_size);
    void push(Figure* fig);
    Figure* operator[](size_t index);
    void remove(size_t index);
    size_t size();
    ~Array();

private:
    size_t _size;
    Figure** arr;
};
