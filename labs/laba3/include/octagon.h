#pragma once

#include <iostream>
#include <string>
#include "figures.h"

class Octagon: public Figure
{
    friend std::ostream& operator<<(std::ostream& os, const Octagon& t);
    friend std::istream& operator>>(std::istream& is, Octagon& t);
public:
    Octagon(): oct{Point(), Point(), Point(), Point(), Point(), Point(), Point(), Point()}{};
    Octagon(Point& ver1, Point& ver2, Point& ver3, Point& ver4, Point& ver5, Point& ver6, Point& ver7, Point& ver8);
    Octagon(const Octagon &other);

    virtual double square() const override;
    virtual Point center() const override;
    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other);
    bool operator==(const Octagon& other);
    virtual operator double() const;

    ~Octagon(){};

    Point oct[8]{};
    size_t size{8};
};

inline std::ostream& operator<<(std::ostream& os, const Octagon& f){
    os << "Octagon's coordinates:"<< std::endl;
    for(size_t i = 0; i < f.size; ++i){
        os << f.oct[i] << std::endl;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Octagon& f){
    std::cout << "Please enter the coordinates of the vertices of the octagon:" << std::endl;
    std::cout << "order [x,y], separated by spaces, the first vertex is the upper left, go clockwise order: " << std::endl;
    for (size_t i = 0; i < f.size; ++i) {
        is >> f.oct[i];
        if (is.fail()) {
            throw std::invalid_argument("Input must be a number");
        }
    }
    for (int i = 0; i < f.size; i++) {
        for (int j = i + 1; j < f.size; j++) {
            if (f.oct[i] == f.oct[j]) {
                throw std::logic_error("Same coordinates for different points");
            }
        }
    }
    return is;
}
