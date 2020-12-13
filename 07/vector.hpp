#pragma once

#include "allocator.hpp"
#include "iterator.hpp"

template<class T, class allocator = Allocator<T>>
class Vector
{
private:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;
    using reference = T &;
    using const_reference = const T &;
    static constexpr size_t ALLOC_SIZE = 4;
private:
    pointer data;
    size_type size_;
    size_type capacity_;
    allocator alloc;
public:
    Vector() : size_(0), capacity_(ALLOC_SIZE)
    {
        alloc = allocator();
        data = alloc.allocate(capacity_);
    }


    Vector(size_type n) : size_(n), capacity_(n * 2)
    {
        if (n == 0) {
            throw std::invalid_argument("n == 0");
        }
        alloc = allocator();
        data = alloc.allocate(capacity_);
    }


    size_type size()
    {
        return size_;
    }


    ~Vector()
    {
        alloc.deallocate(data, capacity_);
    }


    size_type capacity()
    {
        return capacity_;
    }


    size_type empty()
    {
        return size_ == 0;
    }


    reference operator [](size_type j)
    {
        return data[j];
    }


    void clear()
    {
        alloc.deallocate(data, capacity_);
        data = alloc.allocate(ALLOC_SIZE);
        size_ = 0;
        capacity_ = ALLOC_SIZE;
    }


    void reserve(size_type n)
    {
        if (n < capacity_) {
            return;
        }
        data = alloc.reallocate(data, capacity_, n);
        capacity_ = n;
    }


    void resize(size_type n)
    {
        data = alloc.reallocate(data, capacity_, n);
        size_ = n;
        capacity_ = n;
    }


    void push_back(const_reference elem)
    {
        data = alloc.add(data, elem, size_, capacity_);
    }


    void pop_back()
    {
        if (size_ == 0) {
            throw std::out_of_range("size = 0");
        }
        size_--;
    }


    template<class... Args>
    void emplace_back(Args&&... args)
    {
        data = alloc.construct(data, size_, capacity_, std::forward<Args>(args)...);
    }


    Iterator<T> begin()
    {
        return Iterator<T>(data);
    }

    Iterator<T> end()
    {
        return Iterator(data + size_);
    }

    ReverseIterator<T> rbegin()
    {
        return ReverseIterator(data + size_ - 1);
    }

    ReverseIterator<T> rend()
    {
        return ReverseIterator(data - 1);
    }
};

