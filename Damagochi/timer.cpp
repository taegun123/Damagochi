#include "timer.h"
#include <iostream>
using namespace std;

Timer::Timer() {
    Reset();
}

void Timer::Reset() {
    startTime = chrono::steady_clock::now();
}

long long Timer::GetElapsedMilliseconds() {
    auto endTime = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

    return duration.count();
}