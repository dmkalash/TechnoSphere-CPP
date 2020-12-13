template<class Type>
Allocator<Type>::Allocator() {};


template<class Type>
Allocator<Type>::Allocator(const Allocator &) {}


template<class Type>
typename Allocator<Type>::pointer
Allocator<Type>::allocate(size_type n) {
    pointer t = new Type[n];
    return t;
}


template<class Type>
typename Allocator<Type>::pointer
Allocator<Type>::reallocate(pointer p, size_type old_n, size_type new_n) {
    pointer t = new Type[new_n];
    for (int i = 0; i < std::min(old_n, new_n); i++) {
        t[i] = std::move(p[i]);
    }
    deallocate(p, old_n);
    return t;
}


template<class Type>
void
Allocator<Type>::deallocate(pointer p, size_type n) {
    if (p != nullptr) {
        delete [] p;
    }
}


template<class Type>
typename Allocator<Type>::pointer
Allocator<Type>::add(pointer p, const_reference elem,
                        size_type &size, size_type &capacity)
{
    if (size == capacity) {
        p = reallocate(p, size, size * 2);
        capacity = size * 2;
    }
    new ((Type*) (p + size)) Type(elem);
    ++size;

    return p;
}


template<class Type>
template<class ...Args>
typename Allocator<Type>::pointer
Allocator<Type>::construct(pointer p, size_type &size, size_type &capacity,
                            Args&&... args)
{
    if (size == capacity) {
        p = reallocate(p, size, size * 2);
        capacity = size * 2;
    }
    new ((Type*) (p + size)) Type(args...);
    ++size;
    return p;
}
