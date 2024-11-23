#include "triangle.h"
#include <math.h>
#include <string>



Triangle::Triangle(): trian{Point(), Point(), Point()} {};

Triangle::Triangle(Point& ver1, Point& ver2, Point& ver3){ 
    trian[0] = ver1; 
    trian[1] = ver2;
    trian[2] = ver3; 
}

Triangle::Triangle(const Triangle& other)
{
    size = other.size;
    for (size_t i = 0; i < size; ++i)
    {
        trian[i] = other.trian[i];
    }
}

double Triangle::square() const{
    double x1 = trian[0].m_x; double y1 = trian[0].m_y;
    double x2 = trian[1].m_x; double y2 = trian[1].m_y;
    double x3 = trian[2].m_x; double y3 = trian[2].m_y;
    double area = abs(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2.0);
    return area;
}

Point Triangle::center() const{
    double sr_x = 0, sr_y = 0;
    std::cout << "Center:" << std::endl;
    for (size_t i = 0; i < size; ++i){
        sr_x += trian[i].m_x;
        sr_y += trian[i].m_y;
    }
    return Point(sr_x / 3.0, sr_y / 3.0);
}

Triangle& Triangle::operator=(const Triangle& other){
    if (this != &other) {
        trian[0] = other.trian[0];
        trian[1] = other.trian[1];
        trian[2] = other.trian[2];
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other){
    if (this != &other) {
        trian[0] = std::move(other.trian[0]);
        trian[1] = std::move(other.trian[1]);
        trian[2] = std::move(other.trian[2]);
    }
    return *this;
}

void sort_tr(double length_tr[]){
    double x;
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

bool Triangle::operator==(const Triangle& other)
{
    int quantity_of_lines = 3;
    double length_tr1[quantity_of_lines]{};
    double length_tr2[quantity_of_lines]{};
    for (size_t i = 0; i < quantity_of_lines; ++i)
    {
        for (size_t j = i + 1; j < quantity_of_lines; ++j)
        {
            length_tr1[i] = sqrt((pow((trian[i].m_x - trian[j].m_x),2) + pow((trian[i].m_y - trian[j].m_y),2)));
            length_tr2[i] = sqrt((pow((other.trian[i].m_x - other.trian[j].m_x),2) + pow((other.trian[i].m_y - other.trian[j].m_y),2)));
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

Triangle::operator double() const{
    return square();
}
