#pragma once

#include <iostream>

class BigInt
{
    int *abs = nullptr;
    int sign = 1;
    size_t data_len = 0;
    size_t mem_len = 0;
    const size_t ALLOC_SIZE = 16;
    size_t get_alloc_count(size_t size) const;
    void normalize();
public:
    BigInt();
    BigInt(int a);
    BigInt(const std::string &s);
    BigInt(const BigInt &a);
    BigInt(BigInt &&a);
    ~BigInt();
    BigInt & operator = (const BigInt &a);
    BigInt & operator = (BigInt &&a);
    BigInt operator + (const BigInt &b) const;
    BigInt operator - (const BigInt &b) const;
    BigInt operator * (const BigInt &b) const;
    BigInt operator - () const;
    bool operator < (const BigInt &a) const;
    bool operator <= (const BigInt &a) const;
    bool operator > (const BigInt &a) const;
    bool operator >= (const BigInt &a) const;
    bool operator == (const BigInt &a) const;
    bool operator != (const BigInt &a) const;
    std::string as_string(bool with_sign = false) const;
    void print_params() const;
    friend std::ostream & operator << (std::ostream &fout, const BigInt &val);
};
