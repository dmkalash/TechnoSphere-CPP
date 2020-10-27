#pragma once
#include <ostream>


class SecondBracketProxy;
class FirstBracketProxy;
class Matrix;


class SecondBracketProxy {
    int &val_;
public:
    SecondBracketProxy(int &val);
    int operator = (int new_val);
    int operator = (const SecondBracketProxy &new_val);
    operator int() const;
};


class FirstBracketProxy {
    int *data_ = nullptr;
    size_t size_ = 0;
public:
    FirstBracketProxy(int *data, size_t size);
    SecondBracketProxy operator [] (size_t col);
};


class Matrix {
    size_t rows_ = 0;
    size_t cols_ = 0;
    int *data_ = nullptr; // заменить на int32_t
public:
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix &a);
    std::pair<size_t, size_t> get_shape() const;
    size_t get_rows() const;
    size_t get_columns() const;
    Matrix operator + (const Matrix &b) const;
    bool operator == (const Matrix &b) const;
    bool operator != (const Matrix &b) const;
    FirstBracketProxy operator [] (size_t ind);
    void operator *= (int c);
    ~Matrix();
    friend std::ostream & operator << (std::ostream &ostream, const Matrix &matrix);
};

