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
    rowNum = r;
    colNum = c;
    mat = new double[rowNum*colNum];
    if( arr.size() == rowNum * colNum ) {
        for(int i=0; i<rowNum*colNum; ++i)
            mat[i] = arr[i];   
    }
    else {
        std::cerr<< "Wrong size of input array" <<std::endl;
        std::abort();
    }
}

Matrix::Matrix(const Matrix& copy) {
    rowNum = copy.rowNum;
    colNum = copy.colNum;
    mat = new double[rowNum*colNum];
    memset(mat, 0, rowNum*colNum*sizeof(double));
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
        return mat[r*rowNum + c];
    }   
    else {
        std::cerr<< "Wrong indexes" <<std::endl;
        std::abort();
    }
}

double& Matrix::operator()(size_t r, size_t c) {
    if( r < rowNum && c < colNum ) {
        return mat[r*rowNum + c];
    }   
    else {
        std::cerr<< "Wrong indexes" <<std::endl;
        std::abort();
    }
}

bool operator==(const Matrix& a, const Matrix& b) {
    if( a.colNum != b.colNum || a.rowNum != b.rowNum ) return false;
    for(int i=0; i<b.rowNum; ++i) {
        for(int j=0; j<b.colNum; ++j) {
            if( b.operator()(i,j) != a(i,j) )
                return false;
        }
    }
    return true;
}

Matrix operator+(const Matrix& a, const Matrix& b) {
    if( a.rowNum == b.rowNum && a.colNum == b.colNum ) {
        Matrix res(a.rowNum, a.colNum);
        for(int i=0; i<a.rowNum; ++i) {
            for(int j=0; j<a.colNum; ++j) {
                res(i,j) = a(i,j) + b(i,j);
            }
        }
        return res;
    }
    else {
        std::cerr<< "Wrong sizes of matrixes" <<std::endl;
        std::abort();
    }
    return Matrix();
}

Matrix Matrix::operator+=(const Matrix& a) {
    if( this->colNum == a.colNum && this->rowNum == a.rowNum ) {
        for(int i=0; i<a.rowNum; ++i) {
            for(int j=0; j<a.colNum; ++j) {
                this->operator()(i,j) = this->operator()(i,j) + a(i,j);
            }
        }
        return *this;
    }
    else {
        std::cerr<< "Wrong sizes of matrixes" <<std::endl;
        std::abort();
    }
    return Matrix();
}

Matrix operator-(const Matrix& a, const Matrix& b) {
    if( a.rowNum == b.rowNum && a.colNum == b.colNum ) {
        Matrix res(a.rowNum, a.colNum);
        for(int i=0; i<a.rowNum; ++i) {
            for(int j=0; j<a.colNum; ++j) {
                res(i,j) = a(i,j) - b(i,j);
            }
        }
        return res;
    }
    else {
        std::cerr<< "Wrong sizes of matrixes" <<std::endl;
        std::abort();
    }
    return Matrix();
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

std::istream& operator>>(std::istream& in, Matrix& x) {
    for(int i=0; i<x.rowNum; ++i) {
        for(int j=0; j<x.colNum; ++j) {
            in>> x(i,j);
        }
    }
    return in;
}
