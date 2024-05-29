#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#endif

using namespace std;

#ifdef _WIN32
double GetCPUUsage() {
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime) == 0)
        return -1.0;

    ULARGE_INTEGER idle, kernel, user;
    memcpy(&idle, &idleTime, sizeof(FILETIME));
    memcpy(&kernel, &kernelTime, sizeof(FILETIME));
    memcpy(&user, &userTime, sizeof(FILETIME));

    return (1.0 - (static_cast<double>(idle.QuadPart) /
                   (static_cast<double>(kernel.QuadPart) + static_cast<double>(user.QuadPart)))) * 100.0;
}
#elif defined(__linux__)
double GetCPUUsage() {
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    if (!file)
        return -1.0;
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow, &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
        // Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else {
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = static_cast<double>(total);
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent;
}
#endif

int main() {
    while (true) {
        double cpuUsage = GetCPUUsage();
        if (cpuUsage >= 0) {
            cout << "CPU Usage: " << cpuUsage << "%" << endl;
        }
        else {
            cout << "Failed to get CPU Usage." << endl;
        }

        // Sleep for a second
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
