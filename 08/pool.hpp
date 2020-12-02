#pragma once

#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <condition_variable>


class ThreadPool
{
    std::vector<std::thread> pool_;
    std::queue<std::packaged_task<void()>> tasks;
    size_t size_;
    std::condition_variable notification;
    std::mutex m;
    void process();
public:
    explicit ThreadPool(size_t pool_size);
    ~ThreadPool();

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};


#include "pool.tpp"
