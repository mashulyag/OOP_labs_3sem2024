#include "point.h"

Point::Point(const Point& other) : m_x(other.m_x), m_y(other.m_y) {}

bool operator==(const Point& left, const Point& right){
    return (left.m_x == right.m_x) && (left.m_y == right.m_y);
}

std::istream& operator>>(std::istream& is, Point& p){
    double x,y;
    std::cout << "Enter 'x' and 'y' :" << std::endl;
    is >> x >> y;
    p.m_x = x;
    p.m_y = y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p){
    os << "(x: " << p.m_x << "; y: " << p.m_y << ")";
    return os;
}
