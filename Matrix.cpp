#include <iostream>
#include <vector>
#include "Matrix.h"

// constuctors & destructors
Matrix::Matrix() {}

Matrix::Matrix(int r, int c) {
    rowNum = r;
    colNum = c;
    mat = new double[rowNum*colNum];
    memset(mat, 0.0, rowNum*colNum*sizeof(double));
    // std::cout<< "---" <<std::endl;
    
    // std::cout<< "---" <<std::endl;
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

void Matrix::transpose() {
    Matrix b(this->colNum, this->rowNum); // make new transposed matrix col x row
    // std::cout<< b <<std::endl;
    std::cout<< std::endl;
    b.print();
    // for(int i=0; i<this->rowNum; ++i) {
    //     for(int j=0; j<this->colNum; ++j) {
    //         b(j,i) = this->operator()(i,j);
    //     }
    // }
    // // std::cout<< b <<std::endl;
    // *this = b;
}

void Matrix::rotate() { 

}

// operations
Matrix Matrix::operator=(const Matrix& a)
{
    this->colNum = a.colNum;
    this->rowNum = a.rowNum;
    for(int i=0; i<a.colNum*a.rowNum; ++i) {
        this->mat[i] = a.mat[i];
    }
    return *this;
}

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

bool Matrix::operator==(const Matrix& a) {
    if( this->colNum != a.colNum || this->rowNum != a.rowNum ) return false;
    for(int i=0; i<a.rowNum; ++i) {
        for(int j=0; j<a.colNum; ++j) {
            if( this->operator()(i,j) != a(i,j) )
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& a)
{
    return !this->operator==(a);
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

Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix res(a.rowNum, b.colNum);
    if( a.colNum == b.rowNum ) {
        for(int i=0; i<a.rowNum; ++i) {
            for(int j=0; j<b.colNum; ++j) {
                double sum = 0;
                for(int k=0; k<a.colNum; ++k) {
                    sum += a(i,k) * b(k, j);
                }
                res(i,j) = sum;
            }
        }
        return res;
    }
    else {
        std::cerr<< "These matrixes cannot be multiplied" <<std::endl;
        std::abort();
    }
}

Matrix Matrix::operator*=(const Matrix& a) {
    Matrix res(a.rowNum, this->colNum);
    if( this->colNum == a.rowNum ) {
        for(int i=0; i<this->rowNum; ++i) {
            for(int j=0; j<a.colNum; ++j) {
                double sum = 0;
                for(int k=0; k<this->colNum; ++k) {
                    sum += this->operator()(i,k) * a(k, j);
                }
                res(i,j) = sum;
            }
        }
        *this = res;
        return *this;
    }
    else {
        std::cerr<< "These matrixes cannot be multiplied" <<std::endl;
        std::abort();
    }
}

Matrix Matrix::operator-=(const Matrix& a) {
    if( this->colNum == a.colNum && this->rowNum == a.rowNum ) {
        for(int i=0; i<a.rowNum; ++i) {
            for(int j=0; j<a.colNum; ++j) {
                this->operator()(i,j) = this->operator()(i,j) - a(i,j);
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

void Matrix::print()
{
    for(int i=0; i<rowNum; ++i) {
        for(int j=0; j<colNum; ++j) {
            std::cout<< mat[i*rowNum+j] <<" ";
        }
        std::cout<<std::endl;
    }
}