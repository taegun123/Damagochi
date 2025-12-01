#pragma once
#include <chrono>
using namespace std;

class Timer {
private:
    chrono::time_point<chrono::steady_clock> startTime;

public:
    Timer();
    void Reset();
    long long GetElapsedMilliseconds();
};