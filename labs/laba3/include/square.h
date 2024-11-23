#pragma once
#include "figures.h"
#include <iostream>
#include <string>
#include <math.h>

class Square : public Figure 
{
    friend std::ostream& operator<<(std::ostream& os, const Square& t);
    friend std::istream& operator>>(std::istream& is, Square& t);

public:
    Square();
    Square(Point& ver1, Point& ver2, Point& ver3, Point& ver4);
    Square(const Square& other);

    virtual double square() const override;
    virtual Point center() const override;
    Square& operator=(const Square& other);
    Square& operator=(Square&& other);
    bool operator==(const Square& other);
    virtual operator double() const;

    ~Square(){};


    Point sq[4];
    size_t size{4};
};

inline std::ostream& operator<<(std::ostream& os, const Square& f){
    os << "Square's coordinates:"<< std::endl;
    for(size_t i = 0; i < f.size; ++i){
        os << f.sq[i] << std::endl;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Square& f){
    std::cout << "Please enter the coordinates of the vertices of the square" << std::endl;
    std::cout << "order [x,y], separated by spaces: " << std::endl;
    for (size_t i = 0; i < f.size; ++i) {
        is >> f.sq[i];
        if (is.fail()) {
            throw std::invalid_argument("Input must be a number");
        }
    }
    for (size_t i = 0; i < f.size; ++i)
    {
        for (size_t j = i + 1; j < f.size; ++j)
        {
            if (f.sq[i] == f.sq[j])
            {
                throw std::logic_error("Same coordinates for different points");
            }
        }
    }
    double length_sq1 = sqrt((pow((f.sq[0].m_x - f.sq[1].m_x),2) + pow((f.sq[0].m_y - f.sq[1].m_y),2)));
    double length_sq2 = sqrt((pow((f.sq[1].m_x - f.sq[2].m_x),2) + pow((f.sq[1].m_y - f.sq[2].m_y),2)));
    double length_sq3 = sqrt((pow((f.sq[2].m_x - f.sq[3].m_x),2) + pow((f.sq[2].m_y - f.sq[3].m_y),2)));
    double length_sq4 = sqrt((pow((f.sq[0].m_x - f.sq[3].m_x),2) + pow((f.sq[0].m_y - f.sq[3].m_y),2)));
    if (length_sq1 != length_sq2 || length_sq1 != length_sq3 || length_sq1 != length_sq4 || 
        length_sq2 != length_sq3 || length_sq2 != length_sq4 || length_sq3 != length_sq4)
    {
        throw std::logic_error("This isn't square");
    }
    return is;
}
