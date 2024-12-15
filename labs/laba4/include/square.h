#pragma once
#include <iostream>
#include <string>
#include <concepts>
#include <math.h>
#include "figures.h"

template <Number T>
class Square : public Figure<T> 
{
public:
    friend std::ostream& operator<<(std::ostream& os, const Square<T>& t)
    {
        os << "Square's coordinates:"<< std::endl;
        for(size_t i = 0; i < t.size; ++i){
            os << t.sq[i] << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Square<T>& t)
    {
        std::cout << "Please enter the coordinates of the vertices of the square" << std::endl;
        std::cout << "order [x,y], separated by spaces: " << std::endl;
        for (size_t i = 0; i < t.size; ++i) {
            is >> t.sq[i];
            if (is.fail()) {
                throw std::invalid_argument("Input must be a number");
            }
        }
        for (size_t i = 0; i < t.size; ++i)
        {
            for (size_t j = i + 1; j < t.size; ++j)
            {
                if (t.sq[i] == t.sq[j])
                {
                    throw std::logic_error("Same coordinates for different points");
                }
            }
        }
        T length_sq1 = sqrt((pow((t.sq[0]._x - t.sq[1]._x),2) + pow((t.sq[0]._y - t.sq[1]._y),2)));
        T length_sq2 = sqrt((pow((t.sq[1]._x - t.sq[2]._x),2) + pow((t.sq[1]._y - t.sq[2]._y),2)));
        T length_sq3 = sqrt((pow((t.sq[2]._x - t.sq[3]._x),2) + pow((t.sq[2]._y - t.sq[3]._y),2)));
        T length_sq4 = sqrt((pow((t.sq[0]._x - t.sq[3]._x),2) + pow((t.sq[0]._y - t.sq[3]._y),2)));
        if (length_sq1 != length_sq2 || length_sq1 != length_sq3 || length_sq1 != length_sq4 || 
            length_sq2 != length_sq3 || length_sq2 != length_sq4 || length_sq3 != length_sq4)
        {
            throw std::logic_error("This isn't square");
        }
        return is;
    }

    Square(): sq{Point<T>(), Point<T>(), Point<T>(), Point<T>()} {}

    Square(Point<T>& ver1, Point<T>& ver2, Point<T>& ver3, Point<T>& ver4)
    {
        sq[0] = ver1;
        sq[1] = ver2;
        sq[2] = ver3;
        sq[3] = ver4;
    }

    Square(const Square<T>& other)
    {
        size = other.size;
    for (size_t i = 0; i < size; ++i)
    {
        sq[i] = other.sq[i];
    }
    }

    virtual T square() const override
    {
        std::cout << "Square:" << std::endl;
        T length_sq1 = sqrt((pow((sq[0]._x - sq[1]._x),2) + pow((sq[0]._y - sq[1]._y),2)));
        T area = length_sq1 * length_sq1;
        return area;
    }

    virtual Point<T> center() const override
    {
        T sr_x = 0, sr_y = 0;
        std::cout << "Center:" << std::endl;
        for (size_t i = 0; i < size; ++i){
            sr_x += sq[i]._x;
            sr_y += sq[i]._y;
        }
        return Point(sr_x / 4.0, sr_y / 4.0);
    }

    Square<T>& operator=(const Square<T>& other)
    {
        if (this != &other) {
            sq[0] = other.sq[0];
            sq[1] = other.sq[1];
            sq[2] = other.sq[2];
            sq[3] = other.sq[3];
        }
        return *this;
    }

    Square<T>& operator=(Square<T>&& other)
    {
        if (this != &other) {
            sq[0] = std::move(other.sq[0]);
            sq[1] = std::move(other.sq[1]);
            sq[2] = std::move(other.sq[2]);
            sq[3] = std::move(other.sq[3]);
        }
        return *this;
    }

    bool operator==(const Square<T>& other)
    {
        T length = sqrt((pow((sq[0]._x - sq[1]._x),2) + pow((sq[0]._y - sq[1]._y),2)));
        T other_length = sqrt((pow((other.sq[0]._x - other.sq[1]._x),2) + pow((other.sq[0]._y - other.sq[1]._y),2)));
        if (length == other_length) return true;
        return false;
    }

    virtual operator double() const
    {
        return square();
    }

    ~Square(){};


    Point<T> sq[4];
    size_t size{4};
};
