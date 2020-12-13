#pragma once
#include <iostream>


template<class Type>
class Iterator
{
    using pointer = Type *;
    using reference = Type &;
    Type *p;

public:
    Iterator() : p(nullptr) {}
    Iterator(Type *np) : p(np) {}
    Iterator(const Iterator &nit) : p(nit.p) {}

    bool operator==(const Iterator& other) const
    {
        return p == (other.p);
    }

    bool operator!=(const Iterator& other) const
    {
        return !(*this == other);
    }

    void operator++()
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        ++p;
    }

    reference operator*() const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return *p;
    }

    pointer operator -> () const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return p;
    }

    Iterator operator + (size_t add) const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return Iterator(p + add);
    }

    Iterator operator - (size_t sub) const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return Iterator(p - sub);
    }
};



template<class Type>
class ReverseIterator
{
    using pointer = Type *;
    using reference = Type &;
    Type *p;

public:
    ReverseIterator() : p(nullptr) {}
    ReverseIterator(Type *np) : p(np) {}
    ReverseIterator(const ReverseIterator &nit) : p(nit.p) {}

    bool operator==(const ReverseIterator& other) const
    {
        return p == other.p;
    }

    bool operator != (const ReverseIterator& other) const
    {
        return !(*this == other);
    }

    void operator++()
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        --p;
    }

    reference operator*() const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return *p;
    }

    pointer operator -> () const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return p;
    }

    ReverseIterator operator + (size_t add) const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return Iterator(p - add);
    }

    ReverseIterator operator - (size_t sub) const
    {
        if (p == nullptr) {
            throw std::runtime_error("p is null");
        }
        return Iterator(p + sub);
    }
};
