#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <chrono>


class Time {
public:
    LARGE_INTEGER startTimer();
    LARGE_INTEGER endTimer();

    static long long int read_QPC();
};

