#include <iostream> 
#include "Matrix.h"

int main() 
{
    int r;
    int c;
    std::cin>> r;
    std::cin>> c;
    std::vector<double> arr;
    Matrix a(r,c);
    Matrix b(r,c);
    std::cin>> a;
    std::cin>> b;

    a+=b;
    std::cout<<std::endl;
    std::cout<< a <<std::endl;

    return 0;
}