#include <iostream> 
#include "Matrix.h"

int main() 
{
    int r;
    int c;
    std::cin>> r;
    std::cin>> c;

    Matrix a(r,c);
    // Matrix b(r,c);
    std::cin>> a;
    // std::cin>> b;

    std::cout<< a.determinant() <<std::endl;

    return 0;
}