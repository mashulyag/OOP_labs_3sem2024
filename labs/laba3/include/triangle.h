#pragma once
#include "figures.h"
#include <iostream>
#include <string>

class Triangle : public Figure
{
    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
    friend std::istream& operator>>(std::istream& is, Triangle& t);
public: 
    Triangle();
    Triangle(Point& ver1, Point& ver2, Point& ver3);
    Triangle(const Triangle& other);

    virtual double square() const override;
    virtual Point  center() const override;
    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other);
    bool operator==(const Triangle& other);
    virtual operator double() const;

    ~Triangle(){};


    Point trian[3];
    size_t size{3};
};

inline std::ostream& operator<<(std::ostream& os, const Triangle& f){
    os << "Triangle's coordinates:"<< std::endl;
    for(size_t i = 0; i < f.size; ++i){
        os << f.trian[i] << std::endl;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Triangle& f){
    std::cout << "Please enter the coordinates of the vertices of the triangle:" << std::endl;
    std::cout << "order [x,y], separated by spaces : " << std::endl;
    for (size_t i = 0; i < f.size; ++i) {
        is >> f.trian[i];
        if (is.fail()) {
            throw std::invalid_argument("Input must be a number");
        }
    }
    if(f.trian[0] == f.trian[1] || f.trian[0] == f.trian[2] || f.trian[1] == f.trian[2]){
        throw std::logic_error("Same coordinates for different points");
    }
    if (f.square() == 0)
    {
        throw std::logic_error("This is straight line");
    }
    return is;
}
