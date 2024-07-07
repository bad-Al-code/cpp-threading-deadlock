#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include "thread.h"

std::mutex mtx1, mtx2;

void threadFunction(int id)
{
    int delay = 2 + std::rand() % 4;

    {
        std::lock_guard<std::mutex> lock(mtx1);
        std::cout << "Thread " << id << " is starting work with a delay of " << delay << " seconds." << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(delay));

    int a = 0, b = 1, c = 0;
    for (int i = 0; i < 10000; ++i)
    {
        c = a + b;
        a = b;
        b = c;
    }

    {
        std::lock_guard<std::mutex> lock(mtx1);
        std::cout << "Thread " << id << " has finished its work after " << delay << " seconds. Last Fibonacci number: " << c << "." << std::endl;
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

void deadlockFunction1()
{
    std::lock_guard<std::mutex> lock1(mtx1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(mtx2);
    std::cout << "Thread 1 acquired both locks." << std::endl;
}

void deadlockFunction2()
{
    std::lock_guard<std::mutex> lock2(mtx2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock1(mtx1);
    std::cout << "Thread 2 acquired both locks." << std::endl;
}

void startDeadlockThreads()
{
    std::thread t1(deadlockFunction1);
    std::thread t2(deadlockFunction2);

    t1.join();
    t2.join();
}
