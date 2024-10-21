#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // 定义互斥锁

void printNumbers(const std::string &threadName) {
    for (int i = 0; i < 5; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // 加锁
        std::cout << threadName << ": " << i << std::endl;
        // 这里 lock_guard 会自动解锁
    }
}

int main() {
    std::thread t1(printNumbers, "Thread 1");
    std::thread t2(printNumbers, "Thread 2");

    t1.join();
    t2.join();

    return 0;
}
