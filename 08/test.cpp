#include <iostream>
#include <exception>
#include <thread>
#include <unistd.h>
#include <future>
#include <queue>
#include <functional>
#include <chrono>

#include "pool.hpp"


int f1() {
    return 1;
}

int f2(int a) {
    return a;
}

int f3(int a, char b) {
    return a + b;
}

int f4() {
    return 4;
}

char f5() {
    return '5';
}

std::string f6(const std::string &s) {
    return s;
}

int f7() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 7;
}

////////////////////////////////////////////////////


void test_1p_1t()
{
    ThreadPool pool(1);
    auto task1 = pool.exec(f1);
    assert(task1.get() == 1);
    std::cout << "OK\n";
}


void test_2p_1t()
{
    ThreadPool pool(2);
    auto task1 = pool.exec(f1);
    assert(task1.get() == 1);
    std::cout << "OK\n";
}


void test_8p_1t()
{
    ThreadPool pool(8);
    auto task1 = pool.exec(f1);
    assert(task1.get() == 1);
    std::cout << "OK\n";
}


void test_1p_2t()
{
    ThreadPool pool(1);
    auto task1 = pool.exec(f1);
    assert(task1.get() == 1);
    std::cout << "OK\n";
}


void test_2p_2t()
{
    ThreadPool pool(2);
    auto task1 = pool.exec(f1);
    assert(task1.get() == 1);
    std::cout << "OK\n";
}


void test_8p_2t()
{
    ThreadPool pool(8);
    auto task1 = pool.exec(f1);
    assert(task1.get() == 1);
    std::cout << "OK\n";
}


void test_4p_dif_types()
{
    ThreadPool pool(4);
    auto task1 = pool.exec(f1);
    auto task2 = pool.exec(f2, 2);
    auto task3 = pool.exec(f3, 1, 2);
    auto task4 = pool.exec(f4);
    auto task5 = pool.exec(f5);
    auto task6 = pool.exec(f6, "6");
    assert(task1.get() == 1);
    assert(task2.get() == 2);
    assert(task3.get() == 3);
    assert(task4.get() == 4);
    assert(task5.get() == '5');
    assert(task6.get() == "6");
    std::cout << "OK\n";
}


void test_big_queue()
{
    constexpr size_t N = 20, n_pool = 4;
    std::cout << "Running " << N << " tasks(1 sec per task) in 4 pools... " << std::flush;

    using clock_t = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock_t> start = clock_t::now();

    ThreadPool pool(n_pool);
    std::vector<std::function<int()>> tasks;
    for (int i = 0; i < N; i++) {
        tasks.push_back(std::function<int()>(f7));
    }
    std::vector<std::future<int>> res;
    for (int i = 0; i < N; i++) {
        res.push_back(pool.exec(tasks[i]));
    }
    for (int i = 0; i < N; i++) {
        assert(res[i].get() == 7);
    }

    std::cout << "OK. Time: "
            << std::chrono::duration_cast<std::chrono::seconds>(clock_t::now() - start).count()
            << " seconds" << std::endl;
}


int main()
{
    test_1p_1t();
    test_2p_1t();
    test_8p_1t();
    test_1p_2t();
    test_2p_2t();
    test_8p_2t();
    test_4p_dif_types();
    test_big_queue();
    return 0;
}
