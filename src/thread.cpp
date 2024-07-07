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
    int delay = 1 + std::rand() % 5;
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << id << " is starting work with a delay of " << delay << " seconds." << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(delay));

    long long result = 0;
    for (int i = 0; i < 1000000; ++i)
    {
        result += 1;
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << id << " hass finished its work after " << delay << " seconds wit result " << result << "." << std::endl;
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
