#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <windows.h>
#include <psapi.h>

// Function to get CPU usage (Windows specific)
double getCPUUsage() {
  PROCESS_INFORMATION pi;
  DWORD dwPercentIdle = 0;

  if (GetProcessInformation(GetCurrentProcess(), &pi, sizeof(pi))) {
    dwPercentIdle = pi.dwIdleTime;
  }

  return 100.0 - (double)dwPercentIdle;
}

// Function to get memory usage (Windows specific)
double getMemoryUsage() {
  MEMORYSTATUSEX ms;

  GlobalMemoryStatusEx(&ms);
  return (double)ms.dwMemoryLoad / 100.0;
}

// Function to get disk usage (Windows specific)
double getDiskUsage(const std::string& driveLetter) {
  ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

  if (!GetDiskFreeSpaceEx(driveLetter.c_str(), &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
    return 0.0;
  }

  return (double)(totalBytes - totalFreeBytes) / totalBytes * 100.0;
}

int main() {
  while (true) {
    double cpuUsage = getCPUUsage();
    double memoryUsage = getMemoryUsage();
    double diskUsage = getDiskUsage("C:"); // Modify drive letter as needed

    std::cout << "CPU Usage: " << cpuUsage << "%" << std::endl;
    std::cout << "Memory Usage: " << memoryUsage << "%" << std::endl;
    std::cout << "Disk Usage (C:): " << diskUsage << "%" << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
