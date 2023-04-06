// #include <iostream>
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Matrix {
private:
    size_t rowNum;
    size_t colNum;
    double* mat;
public:
    // constuctors & destructors
    Matrix();
    Matrix(int, int); // initialize nxm empty matrix (filled with 0)
    Matrix(int, int, const std::vector<double>); // ilitialize nxm matrix with given array
    Matrix(const Matrix&); // copy constructor
    ~Matrix(); 

    // core functions
    int getRowNum() {return rowNum;};
    int getColNum() {return colNum;};
    void print();

    // operations
    void transpose(Matrix&);
    void rotate(Matrix&);
    double determinant(Matrix&);

    // overloaded operators
    double operator()(size_t, size_t) const;
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, const Matrix&);
};

#endif