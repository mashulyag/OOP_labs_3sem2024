#pragma once

#include <iostream>
#include <string>
#include <concepts>

template <typename T>
concept _point = std::integral<T> || std::floating_point<T>;

template <_point T>
class Point
{
public:
    friend bool operator==(const Point<T>& left, const Point<T>& right)
    {
        return (left._x == right._x) && (left._y == right._y);
    }
    friend std::istream& operator>>(std::istream& is, Point<T>& p)
    {
        double x,y;
        std::cout << "Enter 'x' and 'y' :" << std::endl;
        is >> x >> y;
        p._x = x;
        p._y = y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p)
    {
        os << "(x: " << p._x << "; y: " << p._y << ")";
        return os;
    }

    Point() = default;
	Point(T x, T y) : 
		_x(x), _y(y){}
    Point(const Point<T>& other) : _x(other._x), _y(other._y){}
	~Point() = default;

public:
    double _x{};
    double _y{};
};
