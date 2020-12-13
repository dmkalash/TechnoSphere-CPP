#pragma once
#include <iostream>
#include <new>


template<class Type>
class Allocator
{
    using value_type = Type;
    using pointer = Type *;
    using const_pointer = const Type *;
    using size_type = std::size_t;
    using reference = Type &;
    using const_reference = const Type &;
public:
    Allocator();
    Allocator(const Allocator &);
    pointer allocate(size_type n);
    pointer reallocate(pointer p, size_type old_n, size_type new_n);
    pointer add(pointer p, const_reference elem, size_type &size, size_type &capacity);
    void deallocate(pointer p, size_type n);

    template<class ...Args>
    pointer construct(pointer p, size_type &size, size_type &capacity, Args&&... args);
};

#include "allocator.tpp"
