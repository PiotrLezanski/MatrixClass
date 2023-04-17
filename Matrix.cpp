#include <iostream>
#include <cstdlib>
#include <vector>
#include "Matrix.h"

// constuctors & destructors
Matrix::Matrix() {}

Matrix::Matrix(int r, int c) {
    rowNum = r;
    colNum = c;
    mat = new double[rowNum*colNum];
    memset(mat, 0.0, rowNum*colNum*sizeof(double));
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
    this->rowNum = copy.rowNum;
    this->colNum = copy.colNum;
    this->mat = new double[rowNum*colNum];
    for(int i=0; i<rowNum*colNum; ++i) 
        this->mat[i] = copy.mat[i];
}

Matrix::~Matrix() {
    if( mat != nullptr ) 
        delete [] mat;
}

void Matrix::transpose() {
    Matrix b(this->colNum, this->rowNum); // make new transposed matrix col x row
    for(int i=0; i<this->rowNum; ++i) {
        for(int j=0; j<this->colNum; ++j) {
            b(j,i) = this->operator()(i,j);
        }
    }
    *this = b;
}

void Matrix::rotate(int times) {
    while(times--) {
        // transpose matrix
        this->transpose();
        // reflect
        for(int i=0; i<rowNum; ++i) {
            for(int j=0; j<colNum/2; ++j) {
                double tmp = this->operator()(i,j);
                this->operator()(i,j) = this->operator()(i,colNum-j-1);
                this->operator()(i,colNum-j-1) = tmp;
            }
        }
    }
}

double Matrix::determinant() const {
    Matrix a(*this);
    if( rowNum == colNum ) {
        for(int i=0; i<rowNum-1; ++i) {
            for(int j=i+1; j<colNum; ++j) {
                double scale = a(j,i) / a(i,i);
                for(int k=i; k<colNum; ++k) {
                    a(j,k) -= (a(i,k) * scale);
                }
            }   
        }

        double deter = 1;
        for(int i=0; i<rowNum; ++i) {
            deter *= a(i,i);
        }
        return deter;
    }
    else {
        std::cerr<< "Can't calculate deterninat of non nxn matrix" <<std::endl;
        std::abort();
    }
}

// operations
Matrix Matrix::operator=(const Matrix& a)
{
    colNum = a.colNum;
    rowNum = a.rowNum;
    mat = (double*)realloc(mat,colNum*rowNum*sizeof(double));
    for(int i=0; i<a.colNum*a.rowNum; ++i) {
        mat[i] = a.mat[i];
    }
    return *this;
}

// overloaded operators
double Matrix::operator()(size_t r, size_t c) const
{
    if( r < rowNum && c < colNum ) {
        return mat[r*colNum + c];
    }   
    else {
        std::cerr<< "Wrong indexes" <<std::endl;
        std::abort();
    }
}

double& Matrix::operator()(size_t r, size_t c) {
    if( r < rowNum && c < colNum ) {
        return mat[r*colNum + c];
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
    for(int i=0; i<x.rowNum*x.colNum; ++i) {
        in>> x.mat[i];   
    }
    return in;
}
