#pragma once
#include <ostream>


class BracketProxy;
class Matrix;


class BracketProxy {
    int *data_ = nullptr;
    size_t size_ = 0;
public:
    BracketProxy(int *data, size_t size);
    int & operator [] (size_t ind);
    const int operator [] (size_t ind) const;
};


class Matrix {
    size_t rows_ = 0;
    size_t cols_ = 0;
    int *data_ = nullptr;
public:
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix &a);
    std::pair<size_t, size_t> get_shape() const;
    size_t get_rows() const;
    size_t get_columns() const;
    Matrix operator + (const Matrix &b) const;
    bool operator == (const Matrix &b) const;
    bool operator != (const Matrix &b) const;
    Matrix & operator = (const Matrix &b);
    BracketProxy operator [] (size_t ind);
    const BracketProxy operator [] (size_t ind) const;
    Matrix & operator *= (int c);
    ~Matrix();
    friend std::ostream & operator << (std::ostream &ostream, const Matrix &matrix);
};

