#include <iostream>
#include <string>

#include "figures.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"
#include "array.h"



int main(){
    Array arr;
    Triangle t1, t2, t3;
    Octagon o1, o2, o3;
    Square s1, s2, s3;
    double sum = 0;
    std::cin >> t1;
    arr.push(&t1);
    std::cout << arr[0]->center() << std::endl;
    std::cout << "Square: " << arr[0]->square() << std::endl;
    std::cout << t1;
    std::cout << "Triangle to comparisons" << std::endl;
    std::cin >> t2;
    arr.push(&t2);
    if (t1 == t2) std::cout << "Triangle 1 = Triangle 2" << std::endl;
    else std::cout << "Triangle 1 != Triangle 2";
    t3 = t1;
    arr.push(&t3);
    std::cout << "Copied 1th triangle" << std::endl;
    std::cout << t3;

    for (size_t i{0}; i < arr.size(); ++i)
        {
            sum = sum + arr[i]->square();
        }

    std::cout << "Total area of triangles: " << sum << std::endl;
    std::cin >> o1;
    arr.push(&o1);
    std::cout << arr[3]->center() << std::endl;
    std::cout << arr[3]->square() << std::endl;
    std::cout << o1;
    std::cout << "Octagon for comparisons" << std::endl;
    std::cin >> o2;
    arr.push(&o2);
    if (o1 == o2) std::cout << "Octagon 1 = Octagon 2" << std::endl;
    else std::cout << "Octagon 1 != Octagon 2" << std::endl;
    o3 = o1;
    arr.push(&o3);
    std::cout << "Copied 1th octagon" << std::endl;
    std::cout << o3;

    std::cin >> s1;
    arr.push(&s1);
    std::cout << arr[6]->center() << std::endl;
    std::cout << arr[6]->square() << std::endl;
    std::cout << s1;
    std::cout << "Square for comparisons" << std::endl;
    std::cin >> s2;
    arr.push(&s2);
    if (s1 == s2) std::cout << "Square 1 = Square 2" << std::endl;
    else std::cout << "Square 1 != Square 2";
    s3 = s1;
    arr.push(&s3);
    std::cout << "Copied 1th square" << std::endl;
    std::cout << s3;

    std::cout << "Deleting the first octagon by index, index starts from 0" << std::endl;
    arr.remove(3);
}
