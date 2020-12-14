#include <iostream>
#include <exception>
#include "vector.hpp"
#include <vector>


void test_vector_constructors()
{
    try {
        Vector<int> v1;
        Vector<int> v2(10);
        Vector<int> v(0);
        std::cout << "FAILED\n";
    } catch (const std::invalid_argument &) {
        std::cout << "OK\n";
    }
    catch(...) {
        std::cout << "FAILED\n";
    }
}


void test_api_with_alloc()
{
    Vector<int> a(1);
    assert(a.size() == 1);
    assert(a.empty() == false);

    a[0] = 10;
    assert(a[0] == 10);

    a.clear();
    assert(a.size() == 0);

    a.reserve(1000);
    assert(a.size() == 0 && a.capacity() == 1000);

    a.resize(101);
    assert(a.size() == 101 && a.capacity() == 101);

    a.clear();
    a.push_back(12);
    Vector<char> b;
    b.push_back('a');
    b.push_back('b');
    assert(a.size() == 1 && b.size() == 2 && a[0] == 12 && b[0] == 'a' && b[1] == 'b');

    Vector<int> c(2);
    c[0] = 1;
    c[1] = 2;
    c.pop_back();
    assert(c.size() == 1 && c[0] == 1);

    Vector<std::string> vs(2);
    vs.push_back("one");
    vs.push_back("two");
    assert(vs.size() == 4 && vs[2] == "one" && vs[3] == "two");

    struct tmp {
        int a_, b_;
        tmp() : a_(0), b_(0) {};
        tmp(int a, int b) : a_(a), b_(b) {};
        int sum() {
            return a_ + b_;
        }
    };

    Vector<tmp> t;
    t.emplace_back(10, 90);
    t.emplace_back(50, 50);
    assert(t.size() == 2 && t[0].sum() == 100 && t[1].sum() == 100);

    t.clear();
    auto tt = tmp(5,5);
    t.push_back(std::move(tt));
    assert(t[0].sum() == 10);

    Vector<int> c1(10);
    c1[0] = 3;
    Vector<int> c2(c1);
    assert(c2[0] == 3);

    Vector<int> c3(10);
    c3[0] = 3;
    Vector<int> c4(std::move(c3));
    assert(c4[0] == 3);

    Vector<int> c5(10);
    c5[0] = 3;
    c5[1] = 0;
    Vector<int> c6;
    c6 = c5;
    c6[1] = 1;
    assert(c6[0] == 3 && c6[1] == 1 && c5[0] == 3 && c5[1] == 0);

    Vector<int> c7(10);
    c7[0] = 3;
    c7[1] = 0;
    Vector<int> c8;
    c8 = std::move(c7);
    c8[1] = 1;
    assert(c8[0] == 3 && c8[1] == 1);

    std::cout << "OK\n";
}


void test_api_with_iter()
{
    Vector<int> a(5);
    for (int i = 0; i < 5; i++) {
        a[i] = i;
    }
    int i = 0;
    auto it = a.begin();
    while (it != a.end()) {
        assert(*it == a[i]);
        ++it; i++;
    }

    i = 4;
    auto it2 = a.rbegin();
    while (it2 != a.rend()) {
        assert(*it2 == a[i]);
        ++it2; i--;
    }

    struct t {
        int a, b;
        t() {}
        t(int a, int b) : a(a), b(b) {}
        int sum() {
            return a + b;
        }
    };

    Vector<t> b(3);
    auto it3 = b.begin();
    auto it4 = it3 + 2;
    assert(it4 - 2 == it3);

    b[0].a = 1; b[0].b = 2;
    assert((*it3).a == 1 && it3->a == 1);

    std::cout << "OK\n";
}


int main()
{
    test_vector_constructors();
    test_api_with_alloc();
    test_api_with_iter();
    return 0;
}
