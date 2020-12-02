ThreadPool::ThreadPool(size_t pool_size) : size_(pool_size)
{
    pool_.resize(pool_size);
    for (int i = 0; i < pool_size; i++) {
        std::thread t(&ThreadPool::process, this);
        pool_[i] = std::move(t);
    }
}


template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>
{
    using result = typename std::result_of<Func(Args...)>::type;

    std::packaged_task<result()> task(std::bind(func, args...));
    auto future = task.get_future();

    {
        std::lock_guard <std::mutex> lock(m);
        tasks.emplace(std::move(task));
    }
    notification.notify_all();
    return future;
}


void ThreadPool::process()
{
    while (true) {
        std::packaged_task<void()> f;
        {
            std::unique_lock <std::mutex> lock(m);
            while (tasks.empty()) {
                notification.wait(lock);
            }
            f = std::move(tasks.front());
            if (!f.valid()) {
                break;
            }
            tasks.pop();
        }
        f();
    }
}


ThreadPool::~ThreadPool()
{
    {
        std::unique_lock <std::mutex> lock(m);
        tasks.push({});
    }
    notification.notify_all();
    for (int i = 0; i < size_; i++) {
        pool_[i].join();
    }
}
