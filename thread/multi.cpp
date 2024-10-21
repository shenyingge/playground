#include <iostream>
#include <thread>
#include <chrono>

// 线程函数，模拟一个长时间运行的任务
void longRunningTask(const std::string &threadName) {
    for (int i = 0; i < 10; ++i) {
        std::cout << threadName << ": " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟一些工作
    }
}

int main() {
    std::thread t1(longRunningTask, "Thread 1");
    std::thread t2(longRunningTask, "Thread 2");

    t1.join();
    t2.join();

    std::cout << "Main thread completed." << std::endl;

    return 0;
}
