#include <iostream> 
#include "Matrix.h"

int main() 
{
    int r;
    int c;
    std::cin>> r;
    std::cin>> c;
    std::vector<double> arr;
    arr.push_back(1.0);
    arr.push_back(2.0);
    arr.push_back(3.0);
    arr.push_back(4.0);
    Matrix m(r,c, arr);

    // std::cin>> m;
    std::cout<< m <<std::endl;

    return 0;
}