#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>

std::shared_mutex rw_mutex; // 定义读写锁
int shared_data = 0;

void readData(const std::string &threadName) {
    std::shared_lock<std::shared_mutex> lock(rw_mutex); // 共享锁，允许多个读者
    std::cout << threadName << " read: " << shared_data << std::endl;
}

void writeData(int value) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex); // 独占锁，只有一个写者
    shared_data = value;
    std::cout << "Writer wrote: " << shared_data << std::endl;
}

int main() {
    std::thread writer(writeData, 42);
    std::thread reader1(readData, "Reader 1");
    std::thread reader2(readData, "Reader 2");

    writer.join();
    reader1.join();
    reader2.join();

    return 0;
}
