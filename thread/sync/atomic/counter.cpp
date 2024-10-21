#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

// 定义一个原子计数器
std::atomic<int> atomicCounter(0);

void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        // 原子递增操作
        atomicCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {

    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << atomicCounter.load() << std::endl;

    return 0;
}
