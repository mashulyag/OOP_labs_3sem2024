#pragma once
#include <iostream>
#include <string>
#include "point.h"

class Figure
{
public:
    Figure() = default;

    virtual double square() const = 0;
    virtual Point center() const = 0;
    virtual operator double() const = 0;

    virtual ~Figure() = default;
};
