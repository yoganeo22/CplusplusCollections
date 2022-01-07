// TimeInterval.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h> 
#include <windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

clock_t begin;
clock_t end;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
    {
    }
    //cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

int main()
{
    double time_spent_s;
    double time_spent_ms;
    int c = 0;

    begin = clock();
    StartCounter();

    for (int i = 0; i < 10000000; i++) {
        c += i;
    }

    end = clock();
    time_spent_s = ((double)end - (double)begin) / CLOCKS_PER_SEC;
    time_spent_ms = ((double)end - (double)begin);

    // CPU time is how many seconds the CPU was busy. (the process CPU time)
    printf("Time Interval (CPU time): %.3lf (s)\n", time_spent_s);
    printf("Time Interval (CPU time): %.3lf (ms)\n\n", time_spent_ms);

    // Wall clock time measures how much time has passed, as if you were looking at the clock on your wall.
    printf("Time Interval (Wall Clock time): %.3lf (ms)\n", GetCounter());

    // In some situation, Wall clock time is alot higher to suggest the process spent a lot of time waiting,
    // rather than doing computation the whole time. 
}


// Output: 
// Time Interval (CPU time): 0.014 (s)
// Time Interval (CPU time): 14.000 (ms)

// Time Interval (Wall Clock time): 14.571 (ms)
