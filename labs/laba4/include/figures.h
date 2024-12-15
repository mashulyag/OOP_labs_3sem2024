#pragma once
#include <iostream>
#include <string>
#include <concepts>
#include "point.h"

template <typename T> 
concept Number = std::is_default_constructible<T>::value || std::integral<T> || std::floating_point<T>;

template <Number T>
class Figure
{
public:
    Figure() = default;

    virtual T square() const = 0;
    virtual Point<T> center() const = 0;
    virtual operator double() const = 0;

    virtual ~Figure() = default;
};
