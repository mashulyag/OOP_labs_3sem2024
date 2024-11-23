#include "square.h"
#include <math.h>
#include <string>

Square::Square(): sq{Point(), Point(), Point(), Point()} {};

Square::Square(Point& ver1, Point& ver2, Point& ver3, Point& ver4)
{
    sq[0] = ver1;
    sq[1] = ver2;
    sq[2] = ver3;
    sq[3] = ver4;
}

Square::Square(const Square& other)
{
    size = other.size;
    for (size_t i = 0; i < size; ++i)
    {
        sq[i] = other.sq[i];
    }
}

double Square::square() const
{
    std::cout << "Square:" << std::endl;
    double length_sq1 = sqrt((pow((sq[0].m_x - sq[1].m_x),2) + pow((sq[0].m_y - sq[1].m_y),2)));
    double area = length_sq1 * length_sq1;
    return area;
}

Point Square::center() const
{
    double sr_x = 0, sr_y = 0;
    std::cout << "Center:" << std::endl;
    for (size_t i = 0; i < size; ++i){
        sr_x += sq[i].m_x;
        sr_y += sq[i].m_y;
    }
    return Point(sr_x / 4.0, sr_y / 4.0);
}

Square& Square::operator=(const Square& other)
{
    if (this != &other) {
        sq[0] = other.sq[0];
        sq[1] = other.sq[1];
        sq[2] = other.sq[2];
        sq[3] = other.sq[3];
    }
    return *this;
}

Square& Square::operator=(Square&& other)
{
    if (this != &other) {
        sq[0] = std::move(other.sq[0]);
        sq[1] = std::move(other.sq[1]);
        sq[2] = std::move(other.sq[2]);
        sq[3] = std::move(other.sq[3]);
    }
    return *this;
}

bool Square::operator==(const Square& other)
{
    double length = sqrt((pow((sq[0].m_x - sq[1].m_x),2) + pow((sq[0].m_y - sq[1].m_y),2)));
    double other_length = sqrt((pow((other.sq[0].m_x - other.sq[1].m_x),2) + pow((other.sq[0].m_y - other.sq[1].m_y),2)));
    if (length == other_length) return true;
    return false;
}

Square::operator double() const
{
    return square();
}
