#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "thread.h"

std::mutex mtx;

void threadFunction(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << id << " is accessing the shared resource." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void startThreads(int numThreads) {
    std::vector<std::thread> threads;
    for (int i = 1; i <= numThreads; ++i) {
        threads.push_back(std::thread(threadFunction, i));
    }

    for (auto& t : threads) {
        t.join();
    }
}

