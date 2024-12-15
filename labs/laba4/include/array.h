#pragma once
#include <concepts>
#include <memory>
#include <iostream>
#include "figures.h"

template <class T>
concept Arrayable = std::is_default_constructible<T>::value;

template <Arrayable T>
class Array
{
public:
    Array(): _size{0}, arr{nullptr} {}

    void resize(size_t new_size)
    {
        _size = new_size;
        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(_size);
        for (size_t i{0}; i < _size; ++i)
        {
            tmp[i] = std::move(arr[i]);
        }
        arr = std::move(tmp);
    }

    void push(T fig)
    {
        resize(_size + 1);
        arr[_size] = std::move(fig);
    }

    T& operator[](size_t index)
    {
        if (index < 0 || index > _size) throw std::invalid_argument("Index out of range");
        return arr[index];
    }

    void remove(size_t index)
    {
        if (_size = 0) throw std::invalid_argument("Array is empty");
        if (index < 0 || index > _size) throw std::invalid_argument("Index out of range");
        _size = _size - 1;
        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(_size);
        arr[index] = nullptr;
        for (size_t i{0}; i < _size; ++i)
        {
            if (arr[i] == nullptr) continue;
            tmp[i] = std::move(arr[i]);
        }
        arr = std::move(tmp);
    }

    size_t size()
    {
        return _size;
    }

    ~Array() {
        delete arr;
        _size = 0;
    }


    size_t _size;
    std::unique_ptr<T[]> arr;
};

