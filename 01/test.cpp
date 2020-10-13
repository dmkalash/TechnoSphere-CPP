#include <iostream>
#include "allocator.h"


void AllocatorCreateAndDeleteTest() {
    constexpr size_t test_num = 1;
    try {
        Allocator alloc;
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void DefaultAllocationTest() {
    constexpr size_t test_num = 2;
    try {
        size_t maxSize = 10;
        Allocator alloc;
        alloc.makeAllocator(maxSize);
        std::cout << "Test " << test_num << ": OK" << std::endl;
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
    }
}


void NullSizeAllocationTest() {
    constexpr size_t test_num = 3;
    try {
        size_t maxSize = 0;
        Allocator alloc;
        alloc.makeAllocator(maxSize);
        alloc.reset();
    }
    catch (const char *s) {
        std::cout << "Test " << test_num << ": OK" << std::endl;
        return;
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void NegativeSizeAllocationTest() {
    constexpr size_t test_num = 4;
    try {
        Allocator alloc;
        alloc.makeAllocator(-1);
    }
    catch (const char *s) {
        std::cout << "Test " << test_num << ": OK" << std::endl;
        return;
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void BigSizeAllocationTest() {
    constexpr size_t test_num = 5;
    try {
        Allocator alloc;
        alloc.makeAllocator(100000);
    }
    catch (const char *s) {
        std::cout << "Test " << test_num << ": OK" << std::endl;
        return;
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void DefaultGetPointersTest() {
    constexpr size_t test_num = 6;
    try {
        Allocator alloc;
        alloc.makeAllocator(100);
        char *t1 = alloc.alloc(50);
        if (t1 == nullptr) {
            throw -1;
        }
        t1[0] = 'a';
        t1[49] = 'a';

        char *t2 = alloc.alloc(50);
        if (t2 == nullptr) {
            throw -1;
        }
        t2[0] = 'b';
        t2[49] = 'b';

        if (t1[0] != 'a' || t2[0] != 'b' || t1[0] != 'a' || t2[49] != 'b') {
            throw -1;
        }
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void OversizeGetPointersTest() {
    constexpr size_t test_num = 7;
    try {
        Allocator alloc;
        alloc.makeAllocator(99);
        char *t1 = alloc.alloc(50);
        if (t1 == nullptr) {
            throw -1;
        }
        t1[0] = 'h';

        char *t2 = alloc.alloc(50);
        if (t2 != nullptr) {
            throw -1;
        }
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void NullSizeGetPointersTest() {
    constexpr size_t test_num = 8;
    try {
        Allocator alloc;
        alloc.makeAllocator(100);
        char *t1 = alloc.alloc(0);
        if (t1 != nullptr) {
            throw -1;
        }
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void AfterNullSizeGetPointersTest() {
    constexpr size_t test_num = 9;
    try {
        Allocator alloc;
        alloc.makeAllocator(100);
        char *t1 = alloc.alloc(0);
        t1 = alloc.alloc(100);
        if (t1 == nullptr) {
            throw -1;
        }
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void FirstOversizeGetPointersTest() {
    constexpr size_t test_num = 10;
    try {
        Allocator alloc;
        alloc.makeAllocator(100);
        char *t1 = alloc.alloc(101);
        if (t1 != nullptr) {
            throw -1;
        }
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


void TwiceAllocatorMakeTest() {
    constexpr size_t test_num = 11;
    try {
        size_t maxSize = 10;
        Allocator alloc;
        alloc.makeAllocator(maxSize);
        alloc.makeAllocator(maxSize);
        std::cout << "Test " << test_num << ": OK" << std::endl;
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
    }
}


void SeveralAllocTest() {
    constexpr size_t test_num = 12;
    try {
        Allocator alloc;
        alloc.makeAllocator(30);
        char *t1 = alloc.alloc(10);
        if (t1 == nullptr) {
            throw -1;
        }
        t1[0] = 'a';

        char *t2 = alloc.alloc(10);
        if (t2 == nullptr) {
            throw -1;
        }
        t2[0] = 'b';

        char *t3 = alloc.alloc(10);
        if (t3 == nullptr) {
            throw -1;
        }
        t3[0] = 'c';

        if (t1[0] != 'a' || t2[0] != 'b' || t3[0] != 'c') {
            throw -1;
        }
    }
    catch (...) {
        std::cout << "Test " << test_num << ": FAILED" << std::endl;
        return;
    }
    std::cout << "Test " << test_num << ": OK" << std::endl;
}


int main() {
    AllocatorCreateAndDeleteTest();
    DefaultAllocationTest();
    NullSizeAllocationTest();
    NegativeSizeAllocationTest();
    BigSizeAllocationTest();
    DefaultGetPointersTest();
    OversizeGetPointersTest();
    NullSizeGetPointersTest();
    AfterNullSizeGetPointersTest();
    FirstOversizeGetPointersTest();
    TwiceAllocatorMakeTest();
    SeveralAllocTest();
    return 0;
}
