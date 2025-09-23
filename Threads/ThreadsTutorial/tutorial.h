#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <list>
#include <mutex>

#pragma region Functions Declaration Header

void PrintElapsedTime(std::chrono::system_clock::time_point start, std::chrono::system_clock::time_point end, std::string threadName);
void Count(unsigned long long maxCounter, std::string threadName);
void Example01();
void Example02();
void Example03();
void Example04();
void Example05();
void Example06();
void Example07();

#pragma endregion

#pragma region Global Variables

std::chrono::system_clock::time_point startDate; //Saves the time when the program starts

//Is recommended and important use always the mutex objects, using pointers o passing by reference the copy
std::mutex* consoleMutex; //mutex used for prevent the console solapation

#pragma endregion

void ThreadTutorialTest()
{
    //They can be initialized in the definition, but I prefer to initialize them here
    startDate = std::chrono::system_clock::now();
    consoleMutex = new std::mutex();

    int exampleUsed = 0;//Change this variable for use diferents examples

    switch (exampleUsed)
    {
    case 1:
        Example01();
        break;
    case 2:
        Example02();
        break;
    case 3:
        Example03();
        break;
    case 4:
        Example04();
        break;
    case 5:
        Example05();
        break;
    case 6:
        Example06();
        break;
    case 7:
        Example07();
        break;
    default:
        break;
    }

    std::cout << "Exaple 0" << exampleUsed << " finished" << std::endl;
    std::string text = "";
    std::getline(std::cin, text);
}

/// <summary>
/// This function receive two time points and calculate and print difference in seconds using.
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
void PrintElapsedTime(std::chrono::system_clock::time_point start, std::chrono::system_clock::time_point end, std::string threadName)
{
    std::chrono::duration<double> elapsedTime = end - start;
    consoleMutex->lock();
    std::cout << "Thread: " << threadName << " - Elapsed time: " << elapsedTime.count() << " seconds" << std::endl;
    consoleMutex->unlock();
}

/// <summary>
/// This function counts until the indicated number is reached.
/// </summary>
/// <param name="maxCounter"></param>
void Count(unsigned long long maxCounter, std::string threadName)
{
    //std::this_thread::sleep_for(std::chrono::seconds(1)); alternative option

    for (unsigned long long i = 0; i < maxCounter; i++)
    {

    }

    std::chrono::system_clock::time_point endDate = std::chrono::system_clock::now();
    PrintElapsedTime(startDate, endDate, threadName);
}

//Very Important!!! when you use Join function, the code don't block until you call Join/Detach for all Threads previously created in parent thread
//You can see this using Example01 and Example02

/// <summary>
/// In this example create 3 threads in a row, the code only stop when main thread enter in the 3 threads.
/// </summary>
void Example01()
{
    unsigned long long totalCount = 1000000000ull;
    std::thread* Counter1 = new std::thread(Count, totalCount, "1");
    std::thread* Counter2 = new std::thread(Count, totalCount, "2");
    std::thread* Counter3 = new std::thread(Count, totalCount, "3");

    Counter1->join();
    Counter2->join();
    Counter3->join();

    Count(totalCount, "0");
}

/// <summary>
/// In this example create 3 threads but I create and Use the first and wait for finish, and create the other two.
/// </summary>
void Example02()
{
    unsigned long long totalCount = 1000000000ull;
    std::thread* Counter1 = new std::thread(Count, totalCount, "1");

    Counter1->join();
    std::thread* Counter2 = new std::thread(Count, totalCount, "2");
    std::thread* Counter3 = new std::thread(Count, totalCount, "3");
    Counter2->join();
    Counter3->join();

    Count(totalCount, "0");
}


/// <summary>
/// In this example create 3 threads in a row, the code don't stop because y use Detach.
/// </summary>
void Example03()
{
    unsigned long long totalCount = 1000000000ull;
    std::thread* Counter1 = new std::thread(Count, totalCount, "1");
    std::thread* Counter2 = new std::thread(Count, totalCount, "2");
    std::thread* Counter3 = new std::thread(Count, totalCount, "3");

    Counter1->detach();
    Counter2->detach();
    Counter3->detach();

    Count(totalCount, "0");
}


/// <summary>
/// This is a version of Example02 but using a list and use one by one
/// </summary>
void Example04()
{
    std::list<std::thread*>* threads = new std::list<std::thread*>();

    unsigned long long totalCount = 1000000000ull;

    for (int i = 0; i < 3; i++)
    {
        std::thread* counterThread = new std::thread(Count, totalCount, std::to_string(i + 1));
        threads->push_back(counterThread);
        counterThread->join();
    }

    Count(totalCount, "0");
}

/// <summary>
/// This is a version of Example03 but using a list and use one by one
/// </summary>
void Example05()
{
    std::list<std::thread*>* threads = new std::list<std::thread*>();

    unsigned long long totalCount = 1000000000ull;

    for (int i = 0; i < 3; i++)
    {
        std::thread* counterThread = new std::thread(Count, totalCount, std::to_string(i + 1));
        threads->push_back(counterThread);
        counterThread->detach();
    }

    Count(totalCount, "0");
}

/// <summary>
/// In this example first of all I check the max concurrency of my CPU
/// Next y create this quantity of threads + extra number, and execute all with join
/// </summary>
void Example06()
{
    unsigned int maxThreads = std::thread::hardware_concurrency();
    std::cout << maxThreads << " concurrent threads are supported." << std::endl;

    int extraThreads = 0;

    std::list<std::thread*>* threads = new std::list<std::thread*>();

    unsigned long long totalCount = 1000000000ull;

    for (int i = 0; i < maxThreads + extraThreads; i++)
    {
        std::thread* counterThread = new std::thread(Count, totalCount, std::to_string(i + 1));
        threads->push_back(counterThread);
    }

    for (std::thread* t : *threads)
    {
        t->join();
    }

    Count(totalCount, "0");
}

/// <summary>
/// This class is used for example07, in this example call a function of a class using threads
/// </summary>
class ThreadTester
{
public:
    ThreadTester() {}
    ~ThreadTester() {}

    void Example07();
private:
    void TestFunction(unsigned long long testInt);
};

void ThreadTester::Example07()
{
    //Start of all indicate the function name & is important
    //Next pass the instance of the class for use
    //Next pass all others variables required for a function
    std::thread* testThread = new std::thread(&ThreadTester::TestFunction, this, 14ull);
    testThread->join();
}

void ThreadTester::TestFunction(unsigned long long testInt)
{
    consoleMutex->lock();
    std::cout << "Number is: " << testInt << std::endl;
    consoleMutex->unlock();
}

void Example07()
{
    ThreadTester* threadTester = new ThreadTester();
    threadTester->Example07();
}