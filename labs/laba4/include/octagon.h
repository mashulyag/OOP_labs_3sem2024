#pragma once

#include <iostream>
#include <string>
#include <concepts>
#include <math.h>
#include "figures.h"

template <Number T>
void sort_o(T length_oct[]){
    size_t quantity_of_side = 8;
    for (size_t i = 0; i < quantity_of_side; ++i)
    {
        for (size_t j = 0; j < quantity_of_side; ++j)
        {
            if (length_oct[i] > length_oct[j]) {
                T x = length_oct[i]; 
                length_oct[i] = length_oct[j];
                length_oct[j] = x;
            }
        }
    }
}

template <Number T>
class Octagon: public Figure<T>
{
public:
    friend std::ostream& operator<<(std::ostream& os, const Octagon<T>& t)
    {
        os << "Octagon's coordinates:"<< std::endl;
        for(size_t i = 0; i < t.size; ++i){
            os << t.oct[i] << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Octagon<T>& t)
    {
        std::cout << "Please enter the coordinates of the vertices of the octagon:" << std::endl;
        std::cout << "order [x,y], separated by spaces" << std::endl;
        for (size_t i = 0; i < t.size; ++i) {
            is >> t.oct[i];
            if (is.fail()) {
                throw std::invalid_argument("Input must be a number");
            }
        }
        for (int i = 0; i < t.size; i++) {
            for (int j = i + 1; j < t.size; j++) {
                if (t.oct[i] == t.oct[j]) {
                    throw std::logic_error("Same coordinates for different points");
                }
            }
        }
        return is;
    }

    Octagon(): oct{Point<T>(), Point<T>(), Point<T>(), Point<T>(), Point<T>(), Point<T>(), Point<T>(), Point<T>()}{}

    Octagon(Point<T>& ver1, Point<T>& ver2, Point<T>& ver3, Point<T>& ver4, Point<T>& ver5, Point<T>& ver6, Point<T>& ver7, Point<T>& ver8)
    {
        Point<T> ver[size] = {ver1, ver2, ver3, ver4, ver5, ver6, ver7, ver8};
        for (size_t i = 0; i < size; ++i)
        {
            oct[i] = ver[i];
        }
    }

    Octagon(const Octagon<T> &other)
    {
        size = other.size;
        for (size_t i = 0; i < size; ++i)
        {
            oct[i] = other.oct[i];
        }
    }

    virtual T square() const override
    {
        T x1 = oct[0]._x; T y1 = oct[0]._y;
        Point<T> center = this->center();
        T R = sqrt(pow((x1 - center._x),2) + pow((y1 - center._y),2));
        T r = R * cos(M_PI / size);
        T area = 0.5 * size * R * r;
        return area;
    }

    virtual Point<T> center() const override
    {
        T sr_x = 0, sr_y = 0;
        for (size_t i = 0; i < size; ++i){
            sr_x += oct[i]._x;
            sr_y += oct[i]._y;
        }
        return Point<T>(sr_x / 8.0, sr_y / 8.0);
    }

    Octagon<T>& operator=(const Octagon<T>& other)
    {
        size = other.size;
        for (size_t i = 0; i < size; ++i)
        {
            oct[i] = other.oct[i];
        }
        return *this;
    }

    Octagon<T>& operator=(Octagon<T>&& other)
    {
        if (this != &other)
        {
            for (size_t i{0}; i < size; ++i)
            {
                oct[i] = std::move(other.oct[i]);
            }
        }
        return *this;
    }

    bool operator==(const Octagon<T>& other)
    {
        size_t quantity_of_lines = 8;
        double length_oct1[quantity_of_lines]{};
        double length_oct2[quantity_of_lines]{};
        for (size_t i = 0; i < quantity_of_lines; ++i)
        {
            for (size_t j = i + 1; j < quantity_of_lines; ++j)
            {
                length_oct1[i] = sqrt((pow((oct[i]._x - oct[j]._x),2) + pow((oct[i]._y - oct[j]._y),2)));
                length_oct2[i] = sqrt((pow((other.oct[i]._x - other.oct[j]._x),2) + pow((other.oct[i]._y - other.oct[j]._y),2)));
            }
        }
        sort_o(length_oct1);
        sort_o(length_oct2);
        int count = 0;
        for (size_t i = 0; i < quantity_of_lines; ++i)
        {
            if (length_oct1[i] == length_oct2[i])
            {
                count++;
            }
        }
        if (count == quantity_of_lines) return true;
        return false;
    }

    virtual operator double() const
    {
        return square();
    }

    ~Octagon(){};

    Point<T> oct[8]{};
    size_t size{8};
};
