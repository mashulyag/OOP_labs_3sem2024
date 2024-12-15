#pragma once
#include <iostream>
#include <string>
#include <concepts>
#include <math.h>
#include "figures.h"

template <Number T>
void sort_tr(T length_tr[]){
    T x;
    size_t quantity_of_lines = 3;
    for (size_t i = 0; i < quantity_of_lines; ++i)
    {
        for (size_t j = 0; j < quantity_of_lines; ++j)
        {
            if (length_tr[i] > length_tr[j]) {
                x = length_tr[i]; 
                length_tr[i] = length_tr[j];
                length_tr[j] = x;
            }
        }
    }
}

template <Number T>
class Triangle : public Figure<T>
{
public: 
    friend std::ostream& operator<<(std::ostream& os, const Triangle<T>& t)
    {   
        os << "Triangle's coordinates:"<< std::endl;
        for(size_t i = 0; i < t.size; ++i){
            os << t.trian[i] << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Triangle<T>& t)
    {
        std::cout << "Please enter the coordinates of the vertices of the triangle:" << std::endl;
        std::cout << "order [x,y], separated by spaces : " << std::endl;
        for (size_t i = 0; i < t.size; ++i) {
            is >> t.trian[i];
            if (is.fail()) {
                throw std::invalid_argument("Input must be a number");
            }
        }
        if(t.trian[0] == t.trian[1] || t.trian[0] == t.trian[2] || t.trian[1] == t.trian[2]){
            throw std::logic_error("Same coordinates for different points");
        }
        if (t.square() == 0)
        {
            throw std::logic_error("This is straight line");
        }
        return is;
    }

    Triangle(): trian{Point<T>(), Point<T>(), Point<T>()} {}

    Triangle(Point<T>& ver1, Point<T>& ver2, Point<T>& ver3)
    {
        trian[0] = ver1; 
        trian[1] = ver2;
        trian[2] = ver3; 
    }

    Triangle(const Triangle<T>& other)
    {
        size = other.size;
        for (size_t i = 0; i < size; ++i)
        {
            trian[i] = other.trian[i];
        }
    }

    virtual T square() const override
    {
        T x1 = trian[0]._x; T y1 = trian[0]._y;
        T x2 = trian[1]._x; T y2 = trian[1]._y;
        T x3 = trian[2]._x; T y3 = trian[2]._y;
        T area = abs(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2.0);
        return area;
    }

    virtual Point<T> center() const override
    {
        T sr_x = 0, sr_y = 0;
        std::cout << "Center:" << std::endl;
        for (size_t i = 0; i < size; ++i){
            sr_x += trian[i]._x;
            sr_y += trian[i]._y;
        }
        return Point<T>(sr_x / 3.0, sr_y / 3.0);
    }

    Triangle<T>& operator=(const Triangle<T>& other)
    {
        if (this != &other) {
            trian[0] = other.trian[0];
            trian[1] = other.trian[1];
            trian[2] = other.trian[2];
        }
        return *this;
    }

    Triangle<T>& operator=(Triangle<T>&& other)
    {
        if (this != &other) {
            trian[0] = std::move(other.trian[0]);
            trian[1] = std::move(other.trian[1]);
            trian[2] = std::move(other.trian[2]);
        }
        return *this;
    }

    bool operator==(const Triangle<T>& other)
    {
        int quantity_of_lines = 3;
        T length_tr1[quantity_of_lines]{};
        T length_tr2[quantity_of_lines]{};
        for (size_t i = 0; i < quantity_of_lines; ++i)
        {
            for (size_t j = i + 1; j < quantity_of_lines; ++j)
            {
                length_tr1[i] = sqrt((pow((trian[i]._x - trian[j]._x),2) + pow((trian[i]._y - trian[j]._y),2)));
                length_tr2[i] = sqrt((pow((other.trian[i]._x - other.trian[j]._x),2) + pow((other.trian[i]._y - other.trian[j]._y),2)));
            }
        }
        sort_tr(length_tr1);
        sort_tr(length_tr2);
        int count = 0;
        for (size_t i = 0; i < quantity_of_lines; ++i)
        {
            if (length_tr1[i] == length_tr2[i])
            {
                count++;
            }
        }
        if (count == quantity_of_lines) return true;
        return false;
    }

    virtual operator T() const
    {
        return square();
    }

    ~Triangle(){};


    Point<T> trian[3];
    size_t size{3};
};
