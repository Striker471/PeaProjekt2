#include "Time.h"
#include <windows.h>

using namespace std;

long long int Time::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}