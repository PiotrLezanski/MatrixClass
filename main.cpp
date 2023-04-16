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
    
    a.rotate(2);

    std::cout<< a <<std::endl;

    return 0;
}