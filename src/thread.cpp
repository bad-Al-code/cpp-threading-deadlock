#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "thread.h"
#include <cstdlib>
#include <ctime>

std::mutex mtx;

void threadFunction(int id)
{
    int delay = 1 + std::rand() % 3;
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << id << " is accessing the shared resource." << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(delay));

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << id << " hass finished its work after " << delay << " seconds." << std::endl;
    }
}

void startThreads(int numThreads)
{
    std::srand(std::time(nullptr));

    std::vector<std::thread> threads;
    for (int i = 1; i <= numThreads; ++i)
    {
        threads.push_back(std::thread(threadFunction, i));
    }

    for (auto &t : threads)
    {
        t.join();
    }
}
