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
    std::cout<< a <<std::endl;

    // 2
    // Matrix a(r,c);
    // std::cin>> a;

    // // std::cout<< "A:" <<std::endl;
    // // std::cout<< a <<std::endl;
    // // std::cout<<std::endl;

    // Matrix b(a);
    // std::cout<< std::endl;
    // std::cout<< b <<std::endl;

    return 0;
}