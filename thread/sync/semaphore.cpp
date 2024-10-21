#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>

sem_t semaphore;
// g++ -std=c++11 -pthread your_program.cpp -o your_program


void task(int id) {
    sem_wait(&semaphore);  // P操作，等待信号量
    std::cout << "Thread " << id << " is accessing the resource.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟资源访问
    std::cout << "Thread " << id << " has released the resource.\n";
    sem_post(&semaphore);  // V操作，释放信号量
}

int main() {
    sem_init(&semaphore, 0, 3);  // 初始化信号量，值为3

    std::vector<std::thread> threads;
    for (int i = 1; i <= 5; ++i) {
        threads.emplace_back(task, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    sem_destroy(&semaphore);  // 销毁信号量
    return 0;
}
