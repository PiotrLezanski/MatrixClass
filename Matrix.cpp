#include <iostream>
#include <vector>
#include "Matrix.h"

// constuctors & destructors
Matrix::Matrix() {}

Matrix::Matrix(int r, int c) {
    rowNum = r;
    colNum = c;
    mat = new double[rowNum*colNum];
    memset(mat, 0, rowNum*colNum*sizeof(double));
}

Matrix::Matrix(int r, int c, const std::vector<double> arr) {
    if( arr.size() == rowNum * colNum ) {
        Matrix(r, c);
        for(int i=0; i<rowNum*colNum; ++i)
            mat[i] = arr[i];   
    }
    else {
        std::cerr<< "Wrong size of input array" <<std::endl;
        std::abort();
    }
}

Matrix::Matrix(const Matrix& copy) {
    Matrix(copy.rowNum, copy.colNum);
    for(int i=0; i<rowNum*colNum; ++i) 
        mat[i] = copy.mat[i];
}

Matrix::~Matrix() {
    if( mat != nullptr ) 
        delete [] mat;
}

// core functions
void Matrix::print()
{
    for(int i=0; i<rowNum; ++i) {
        for(int j=0; j<colNum; ++j) {
            std::cout<< mat[i*rowNum+j] <<" ";
        }
        std::cout<<std::endl;
    }
}

// operations


// overloaded operators

double Matrix::operator()(size_t r, size_t c) const
{
    if( r < rowNum && c < colNum ) {
        return mat[r*rowNum + colNum];
    }   
    else {
        std::cerr<< "Wrong indexes" <<std::endl;
        std::abort();
    }
}

std::ostream& operator<<(std::ostream& out, const Matrix& x) {
    for(int i=0; i<x.rowNum; ++i) {
        for(int j=0; j<x.colNum; ++j) {
            out<< x(i, j) << " ";
        }
        out<< std::endl;
    }
    return out;
}

// std::istream& operator>>(std::istream& in, const Matrix& x) {
//     for(auto &a : x) {
//         in >> a;
//     }
//     return in;
// }
