#include "array.h"

Array::Array(): _size{0}, arr{nullptr}
{
    Figure** arr = new Figure* [_size];
    
}

void Array::resize(size_t new_size)
{
    Figure** tmp = new Figure*[new_size];
    for (size_t i{0}; i < new_size; ++i) tmp[i] = nullptr;
    // for (size_t i{0}; i < new_size; ++i)
    // {
    //     tmp[i] = nullptr;
    // }
    for (size_t i{0}; i < _size; ++i)
    {
        tmp[i] = arr[i];
    }
    delete [] arr;
    arr = tmp;
    _size = new_size;
}

size_t Array::size()
{
    return _size;
}

void Array::push(Figure* fig)
{
    resize(_size + 1);
    arr[_size - 1] = fig;
}

void Array::remove(size_t index)
{
    if (_size = 0) throw std::invalid_argument("Array is empty");
    if (index < 0 || index > _size) throw std::invalid_argument("Index out of range");
    Figure** tmp = new Figure*[_size];
    for (size_t i{0}; i < _size; ++i) tmp[i] = nullptr;
    arr[index] = nullptr;
    for (size_t i{0}; i < _size; ++i)
    {
        if (arr[i] == nullptr) continue;
        tmp[i] = arr[i];
    }
    delete [] arr;
    arr = tmp;
    _size = _size - 1;
}

Figure* Array::operator[](size_t index)
{
    if (index < 0 || index > _size) throw std::invalid_argument("Index out of range");
    return arr[index];
}

Array::~Array()
{
    _size = 0;
    delete [] arr;
    arr = nullptr;
}
