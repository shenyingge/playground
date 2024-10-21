#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void printNumbers(const std::string &threadName) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; }); // 当前线程会释放锁，等待条件变量通知
    for (int i = 0; i < 5; ++i) {
        std::cout << threadName << ": " << i << std::endl;
    }
}

void setReady() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟准备工作
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all(); // 通知所有等待线程
}

int main() {
    std::thread t1(printNumbers, "Thread 1");
    std::thread t2(printNumbers, "Thread 2");
    std::thread t3(setReady);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
