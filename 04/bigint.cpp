#include <new>
#include <exception>
#include <algorithm>

#include "bigint.h"


size_t BigInt::get_alloc_count(size_t size) const
{
    return size / ALLOC_SIZE + (size % ALLOC_SIZE != 0);
}


BigInt::BigInt()
{
    abs = new int[ALLOC_SIZE];
    for (int i = 0; i < ALLOC_SIZE; i++) {
        abs[i] = 0;
    }
    data_len = 1;
    sign = 1;
    mem_len = ALLOC_SIZE;
}


BigInt::BigInt(int a)
{
    unsigned int t = a;
    sign = 1;
    if (a < 0) {
        sign = -1;
        t = -(1LL * a);
    }
    data_len = 0;
    if (t == 0) {
        data_len = 1;
    }
    mem_len = get_alloc_count(10) * ALLOC_SIZE;
    abs = new int[mem_len];
    for (int i = 0; i < mem_len; i++) {
        abs[i] = 0;
    }
    while (t > 0) {
        abs[data_len++] = t % 10;
        t /= 10;
    }
}


BigInt::BigInt(const std::string &s)
{
    if (s.size() == 0) {
        throw "String is empty";
    }
    size_t shift = false;
    if (s[0] == '-') {
        sign = -1;
        shift = 1;
    } else if (s[0] == '+') {
        sign = 1;
        shift = 1;
    }
    bool is_zero = true;
    for (size_t i = shift; i < s.size(); i++) {
        if (!isdigit(s[i])) {
            throw "Invalid string";
        }
        if (s[i] == '0' && is_zero) {
            shift++;
        } else {
            is_zero = false;
        }
    }
    data_len = std::max(1ul, s.size() - shift);
    mem_len = get_alloc_count(data_len) * ALLOC_SIZE;
    abs = new int[mem_len];
    for (int i = 0; i < mem_len; i++) {
        abs[i] = 0;
    }
    for (int i = shift; i < s.size(); i++) {
        abs[s.size() - i - 1] = s[i] - '0';
    }
    if (abs[0] == 0 && data_len == 1) {
        sign = 1;
    }
}


BigInt::BigInt(const BigInt &a) : sign(a.sign), data_len(a.data_len), mem_len(a.mem_len)
{
    if (a.abs == nullptr) {
        abs = nullptr;
        mem_len = data_len = 0;
        sign = 1;
    }
    else {
        abs = new int[mem_len];
        for (int i = 0; i < data_len; i++) {
            abs[i] = a.abs[i];
        }
        for (int i = data_len; i < mem_len; i++) {
            abs[i] = 0;
        }
    }
}


BigInt::BigInt(BigInt &&a) : sign(std::move(a.sign)),
                                        data_len(std::move(a.data_len)),
                                        mem_len(std::move(a.mem_len))
{
    abs = a.abs;
    a.abs = nullptr;
    a.data_len = 0;
    a.mem_len = 0;
    a.sign = 1;
}


BigInt::~BigInt()
{
    if (abs != nullptr) {
        delete [] abs;
    }
}


BigInt & BigInt::operator = (const BigInt &a)
{
    if (this == &a) {
        return *this;
    }

    int *tmp = new int[a.mem_len];
    for (int i = 0; i < a.mem_len; i++) {
        tmp[i] = 0;
    }
    if (abs != nullptr) {
        delete [] abs;
    }
    abs = tmp;
    mem_len = a.mem_len;
    data_len = a.data_len;
    sign = a.sign;
    for (int i = 0; i < a.mem_len; i++) {
        abs[i] = a.abs[i];
    }
    return *this;
}


BigInt & BigInt::operator = (BigInt &&a)
{
    if (this == &a) {
        return *this;
    }
    if (abs != nullptr) {
        delete [] abs;
    }
    abs = a.abs;
    mem_len = std::move(a.mem_len);
    data_len = std::move(a.data_len);
    sign = std::move(a.sign);

    a.abs = nullptr;
    a.mem_len = 0;
    a.data_len = 0;
    a.sign = 1;

    return *this;
}


BigInt BigInt::operator + (const BigInt &b) const
{
    if (b == BigInt(0)) {
        return *this;
    } else if (*this == BigInt(0)) {
        return b;
    }

    if (this->sign == b.sign) {
        //std::cout << "ENTER IF\n";
        BigInt a;
        //std::cout << "CREATE a\n";
        if (data_len > b.data_len) {
            a = *this;
        } else {
            a = b;
        }

        int carry = 0;
        int i = 0;
        while (i < std::min(data_len, b.data_len)) {
            a.abs[i] = (abs[i] + b.abs[i] + carry) % 10;
            carry = (abs[i] + b.abs[i] + carry) / 10;
            ++i;
        }
        while (i < data_len) {
            a.abs[i] = (abs[i] + carry) % 10;
            carry = (abs[i] + carry) / 10;
            ++i;
        }
        while (i < b.data_len) {
            a.abs[i] = (b.abs[i] + carry) % 10;
            carry = (b.abs[i] + carry) / 10;
            ++i;
        }
        if (carry != 0) {
            if (i == mem_len) {
                int *tmp = new int[a.mem_len + ALLOC_SIZE];
                for (int j = 0; j < i; j++) {
                    tmp[j] = a.abs[j];
                }
                for (int j = i; j < a.mem_len + ALLOC_SIZE; j++) {
                    tmp[j] = 0;
                }
                delete[] a.abs;
                a.abs = tmp;
                a.mem_len = a.mem_len + ALLOC_SIZE;
            }
            a.abs[i] = carry;
            a.data_len = i + 1;
        }
        a.normalize();
        return a;
    } else {
        return *this - (-b);
    }
}


BigInt BigInt::operator - (const BigInt &b) const
{
    if (b == BigInt(0)) {
        return *this;
    } else if (*this == BigInt(0)) {
        return -b;
    }

    if (this->sign == b.sign) {
        int res_sign;
        BigInt d1, d2;
        if (sign == 1) {
            if (*this >= b) {
                res_sign = 1;
                d1 = *this;
                d2 = b;
            } else {
                res_sign = -1;
                d1 = b;
                d2 = *this;
            }
        } else {
            if (b >= *this) {
                res_sign = -1;
                d1 = *this;
                d2 = b;
            } else {
                res_sign = 1;
                d1 = b;
                d2 = *this;
            }
        }
        d1.sign = res_sign;

        int carry = 0;
        int i = 0;
        while (i < d2.data_len) { // -(1234 - 0)
            int t = d1.abs[i] - d2.abs[i] - carry;
            d1.abs[i] = (t + 10) % 10;
            carry = (t < 0);
            ++i;
        }
        while (i < d1.data_len) {
            int t = d1.abs[i] - carry;
            d1.abs[i] = (t + 10) % 10;
            carry = (t < 0);
            ++i;
        }
        d1.normalize();
        return d1;

    } else {
        return *this + (-b);
    }
}


BigInt BigInt::operator * (const BigInt &a) const
{
    BigInt res;
    res.mem_len = get_alloc_count(this->data_len + a.data_len) * ALLOC_SIZE;
    if (res.abs != nullptr) {
        delete [] res.abs;
    }
    res.abs = new int[res.mem_len];
    for (int i = 0; i < res.mem_len; i++) {
        res.abs[i] = 0;
    }
    res.sign = a.sign * this->sign;
    int carry = 0;
    for (int i = 0; i < this->data_len; i++) {
        for (int j = 0; j < a.data_len; j++) {
            long long cur = res.abs[i + j] + this->abs[i] * a.abs[j];
            res.abs[i + j] = (carry + cur) % 10;
            carry = (carry + cur) / 10;
        }
        res.abs[i + a.data_len] += carry;
        carry = 0;
    }
    res.data_len = this->data_len + a.data_len;
    res.normalize();
    return res;
}


BigInt BigInt::operator - () const
{
    BigInt res = *this;
    if (*this != BigInt(0)) {
        res.sign = -res.sign;
    }
    return res;
}


bool BigInt::operator < (const BigInt &a) const
{
    if (this->sign == -1 && a.sign == 1) {
        return true;
    }
    if (this->sign == 1 && a.sign == -1) {
        return false;
    }

    bool inv = false;
    if (this->sign == -1) {
        inv = true;
    }

    if (this->data_len < a.data_len) {
        return true ^ inv;
    }
    if (this->data_len > a.data_len) {
        return false ^ inv;
    }

    for (int i = this->data_len - 1; i >= 0; --i) {
        if (this->abs[i] < a.abs[i]) {
            return true ^ inv;
        } else if (this->abs[i] > a.abs[i]) {
            return false ^ inv;
        }
    }
    return false;
}


bool BigInt::operator <= (const BigInt &a) const
{
    return !(*this > a);
}


bool BigInt::operator > (const BigInt &a) const
{
    return (a < *this);
}


bool BigInt::operator >= (const BigInt &a) const
{
    return !(*this < a);
}


bool BigInt::operator == (const BigInt &a) const
{
    return !(*this < a) && !(a < *this);
}


bool BigInt::operator != (const BigInt &a) const
{
    return !(*this == a);
}


std::string BigInt::as_string(bool with_sign) const
{
    std::string res = "";
    if (this->sign == -1) {
        res = "-";
    } else if (with_sign) {
        res = "+";
    }
    for (int i = this->data_len - 1; i >= 0; i--) {
        res += this->abs[i] + '0';
    }
    return res;
}


std::ostream & operator << (std::ostream &fout, const BigInt &val)
{
    if (val.sign == -1) {
        fout << "-";
    }
    for (int i = val.data_len - 1; i >= 0; i--) {
        fout << val.abs[i];
    }
    return fout;
}


void BigInt::normalize()
{
    if (abs == nullptr) {
        sign = 1;
        data_len = 0;
        mem_len = 0;
        return;
    }
    int i = data_len;
    while (i >= 0 && abs[i] == 0) {
        i--;
    }
    data_len = i + 1;
    if (i < 0) {
        data_len = 1;
        sign = 1;
    }
    size_t needed_size = this->get_alloc_count(data_len) * ALLOC_SIZE;
    if (needed_size < mem_len) {
        int *tmp = new int[needed_size];
        for (int i = 0; i < needed_size; i++) {
            tmp[i] = abs[i];
        }
        delete [] abs;
        abs = tmp;
    }
}


void BigInt::print_params() const
{
    std::cout << "\n\nBigInt:\n";
    std::cout << "\tALLOC_SIZE: " << ALLOC_SIZE << "\n";
    std::cout << "\tPOINTER: " << this << "\n";
    std::cout << "\tsign: " << sign << "\n\tdata_len: " << data_len << "\n\tmem_len: " << mem_len << "\n";
    for (int i = data_len - 1; i >= 0; i--) {
        std::cout << abs[i];
    }
    std::cout << "\n";
}
