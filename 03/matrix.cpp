#include <exception>
#include <new>

#include "matrix.h"


Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols)
{
    if (rows_ == 0 || cols_ == 0) {
        throw std::string("Null dimensions not allowed");
    }
    data_ = new int[rows_ * cols_];
    if (!data_) {
        throw std::bad_alloc();
    }
}


Matrix::Matrix(const Matrix &a)
{
    auto size = a.get_shape();
    rows_ = size.first;
    cols_ = size.second;
    data_ = new int[rows_ * cols_];
    if (!data_) {
        throw std::bad_alloc();
    }

    for (size_t i = 0; i < rows_ * cols_; i++) {
        data_[i] = a.data_[i];
    }
}


std::pair<size_t, size_t> Matrix::get_shape() const
{
    return {rows_, cols_};
}


size_t Matrix::get_rows() const
{
    return rows_;
}


size_t Matrix::get_columns() const
{
    return cols_;
}


Matrix Matrix::operator + (const Matrix &b) const
{
    if (this->get_shape() != b.get_shape()) {
        throw "Shapes are different!";
    }
    Matrix res(b);
    for (size_t i = 0; i < rows_ * cols_; i++) {
        res.data_[i] += this->data_[i];
    }
    return res;
}


bool Matrix::operator == (const Matrix &b) const
{
    if (this->get_shape() != b.get_shape()) {
        return false;
    }
    for (size_t i = 0; i < rows_ * cols_; i++) {
        if (this->data_[i] != b.data_[i]) {
            return false;
        }
    }
    return true;
}


bool Matrix::operator != (const Matrix &b) const
{
    return !(*this == b);
}


void Matrix::operator *= (int c)
{
    for (int i = 0; i < rows_ * cols_; i++) {
        this->data_[i] *= c;
    }
}


Matrix::~Matrix()
{
    delete[] data_;
}


FirstBracketProxy Matrix::operator [] (size_t ind)
{
    if (this->rows_ < ind) {
        throw std::out_of_range("Out of range for axis 0");
    }
    return FirstBracketProxy(data_ + ind * cols_, cols_);
}


std::ostream & operator << (std::ostream &ostream, const Matrix &matrix)
{
    auto size = matrix.get_shape();
    for (size_t i = 0; i < size.first; i++) {
        for (size_t j = 0; j < size.second; j++) {
            ostream << matrix.data_[i * matrix.cols_ + j] << " ";
        }
        ostream << std::endl;
    }
    return ostream;
}



FirstBracketProxy::FirstBracketProxy(int *data, size_t size) : data_(data), size_(size) {}


SecondBracketProxy FirstBracketProxy::operator [] (size_t ind)
{
    if (ind >= size_) {
        throw std::out_of_range("Out of range for axis 1");
    }
    return SecondBracketProxy(data_[ind]);
}



SecondBracketProxy::SecondBracketProxy(int &val) : val_(val) {}


int SecondBracketProxy::operator = (int new_val)
{
    val_ = new_val;
    return val_;
}


int SecondBracketProxy::operator = (const SecondBracketProxy &new_val)
{
    val_ = new_val.val_;
    return val_;
}


SecondBracketProxy::operator int() const
{
    int new_int = val_;
    return new_int;
}
