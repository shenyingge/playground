#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int cnt = 100000;

void printNumbers(const std::string& threadName) {
    for (int i = 0; i < 50000; ++i) {
        // unique_lock 作用域结束自动释放，不用手动 unlock
        std::unique_lock<std::mutex> lock(mtx);
        cnt--;
    }
}

int main() {
    std::thread t1(printNumbers, "Thread 1");
    std::thread t2(printNumbers, "Thread 2");

    t1.join();
    t2.join();
    std::cout<<"cnt: "<<cnt<<std::endl;

    return 0;
}
