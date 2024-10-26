#include "octagon.h"
#include <math.h>

Octagon::Octagon(Point& ver1, Point& ver2, Point& ver3, Point& ver4, Point& ver5, Point& ver6, Point& ver7, Point& ver8)
{
    Point ver[size] = {ver1, ver2, ver3, ver4, ver5, ver6, ver7, ver8};
    for (size_t i = 0; i < size; ++i)
    {
        oct[i] = ver[i];
    }
}

Octagon::Octagon(const Octagon& other)
{
    size = other.size;
    for (size_t i = 0; i < size; ++i)
    {
        oct[i] = other.oct[i];
    }
    
}

Point Octagon::center() const
{
    double sr_x = 0, sr_y = 0;
    for (size_t i = 0; i < size; ++i){
        sr_x += oct[i].m_x;
        sr_y += oct[i].m_y;
    }
    return Point(sr_x / 8.0, sr_y / 8.0);
}

double Octagon::square() const 
{
    double x1 = oct[0].m_x; double y1 = oct[0].m_y;
    Point center = this->center();
    double R = sqrt(pow((x1 - center.m_x),2) + pow((y1 - center.m_y),2));
    double r = R * cos(M_PI / size);
    double area = 0.5 * size * R * r;
    return area;
}

Octagon& Octagon::operator=(const Octagon& other)
{
    if (this != &other)
    {
        for (size_t i{0}; i < size; ++i)
        {
            oct[i] = other.oct[i];
        }
    }
    return *this;
}

Octagon& Octagon::operator=(Octagon&& other)
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

void sort_o(double length_oct[]){
    size_t quantity_of_side = 8;
    for (size_t i = 0; i < quantity_of_side; ++i)
    {
        for (size_t j = 0; j < quantity_of_side; ++j)
        {
            if (length_oct[i] > length_oct[j]) {
                double x = length_oct[i]; 
                length_oct[i] = length_oct[j];
                length_oct[j] = x;
            }
        }
    }
}

bool Octagon::operator==(const Octagon& other)
{
    size_t quantity_of_lines = 8;
    double length_oct1[quantity_of_lines]{};
    double length_oct2[quantity_of_lines]{};
    for (size_t i = 0; i < quantity_of_lines; ++i)
    {
        for (size_t j = i + 1; j < quantity_of_lines; ++j)
        {
            length_oct1[i] = sqrt((pow((oct[i].m_x - oct[j].m_x),2) + pow((oct[i].m_y - oct[j].m_y),2)));
            length_oct2[i] = sqrt((pow((other.oct[i].m_x - other.oct[j].m_x),2) + pow((other.oct[i].m_y - other.oct[j].m_y),2)));
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

Octagon::operator double() const
{
    return square();
}
