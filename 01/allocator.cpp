#include <string>
#include "allocator.h"


Allocator::Allocator() {
    mem = nullptr;
    alloc_size = 0;
    offset = 0;
}


void Allocator::makeAllocator(size_t maxSize) {
    if (maxSize == 0) {
        throw "Zero size";
    }
    try {
        if (mem != nullptr) {
            delete [] mem;
        }
        mem = new char[maxSize];
        alloc_size = maxSize;
    }
    catch(...) {
        throw "Allocation error";
    }
}


char* Allocator::alloc(size_t size) {
    if (offset + size <= alloc_size && size != 0) {
        char *ret = mem + offset;
        offset += size;
        return ret;
    } else {
        return nullptr;
    }
}


void Allocator::reset() {
    alloc_size = 0;
    offset = 0;
}


Allocator::~Allocator() {
    if (mem != nullptr) {
        delete [] mem;
    }
};

