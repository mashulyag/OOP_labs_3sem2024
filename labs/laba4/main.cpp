#include <iostream>
#include <string>
#include <memory>

#include "figures.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"
#include "array.h"

int main(){
    std::unique_ptr<Triangle<double>> t = std::make_unique<Triangle<double>>();
    //std::unique_ptr<Octagon<double>> o = std::make_unique<Octagon<double>>();
    std::unique_ptr<Square<double>> s = std::make_unique<Square<double>>();
    std::cin >> *t >> *s;
    std::cout << *t << *s << std::endl;
    
    // // std::unique_ptr<Octagon<double>> o = std::make_unique<Octagon<double>>();
    // // std::cin >> *o;
    // Array<std::unique_ptr<Figure<double>>> array{};
    // // array.push(std::move(o));
    // std::cout << *array[0] << std::endl;
    // //std::cout << *o << std::endl;
    // Point<double> p;
    // std::cin >> p;
    // std::cout << p;

}
