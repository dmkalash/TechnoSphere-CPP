#include <exception>
#include <new>

#include "matrix.h"


Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols)
{
    if (rows_ == 0 || cols_ == 0) {
        throw std::string("Null dimensions not allowed");
    }
    data_ = new int[rows_ * cols_];
}


Matrix::Matrix(const Matrix &a)
{
    auto size = a.get_shape();
    rows_ = size.first;
    cols_ = size.second;
    data_ = new int[rows_ * cols_];

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


Matrix & Matrix::operator = (const Matrix &b)
{
    if (this == &b) {
        return *this;
    }

    rows_ = b.get_rows();
    cols_ = b.get_columns();

    delete [] data_;
    data_ = new int[rows_ * cols_];

    for (size_t i = 0; i < rows_ * cols_; i++) {
        data_[i] = b.data_[i];
    }
    return *this;
}


Matrix & Matrix::operator *= (int c)
{
    for (int i = 0; i < rows_ * cols_; i++) {
        this->data_[i] *= c;
    }
    return *this;
}


Matrix::~Matrix()
{
    delete[] data_;
}


BracketProxy Matrix::operator [] (size_t ind)
{
    if (this->rows_ < ind) {
        throw std::out_of_range("Out of range for axis 0");
    }
    return BracketProxy(data_ + ind * cols_, cols_);
}


const BracketProxy Matrix::operator [] (size_t ind) const
{
    if (this->rows_ < ind) {
        throw std::out_of_range("Out of range for axis 0");
    }
    return BracketProxy(data_ + ind * cols_, cols_);
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


BracketProxy::BracketProxy(int *data, size_t size) : data_(data), size_(size) {}


int & BracketProxy::operator [] (size_t ind)
{
    if (ind >= size_) {
        throw std::out_of_range("Out of range for axis 1");
    }
    return data_[ind];
}


const int BracketProxy::operator [] (size_t ind) const
{
    if (ind >= size_) {
        throw std::out_of_range("Out of range for axis 1");
    }
    return data_[ind];
}

