#include <iostream>
#include <thread>
#include <mutex>
#include "thread.h"

std::mutex mtx;

void threadFunction(int id) {
    mtx.lock();
    std::cout << "Thread " << id << " is accessing the shared resource." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx.unlock();
}

void startThreads() {
    std::thread t1(threadFunction, 1);
    std::thread t2(threadFunction, 2);

    t1.join();
    t2.join();
}

