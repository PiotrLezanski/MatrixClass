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
    
    a.transpose();

    std::cout<<std::endl;
    // std::cout<< a <<std::endl;

    return 0;
}