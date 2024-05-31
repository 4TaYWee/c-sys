#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <future>

// Function to get CPU usage (Linux specific)
double getCPUUsage() {
  std::ifstream cpuStat("/proc/stat");
  std::vector<long long> cpuData(10);
  cpuStat >> cpuData[0]; // Skip the first element (cpu identifier)
  for (int i = 1; i < 6; i++) {
    cpuStat >> cpuData[i];
  }
  cpuStat.close();

  // Repeat to get second set of data
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  cpuStat.open("/proc/stat");
  std::vector<long long> cpuData2(10);
  cpuStat >> cpuData2[0];
  for (int i = 1; i < 6; i++) {
    cpuStat >> cpuData2[i];
  }
  cpuStat.close();

  // Calculate CPU usage
  long long totalTime = 0;
  for (int i = 1; i < 6; i++) {
    totalTime += cpuData2[i] - cpuData[i];
  }
  long long idleTime = cpuData2[4] - cpuData[4];
  return (double)(totalTime - idleTime) / totalTime * 100;
}

// Function to get memory usage (Cross-platform)
double getMemoryUsage() {
  // Implement based on your OS (e.g., using WMI on Windows or parsing /proc/meminfo on Linux)
  std::ifstream meminfo;
  // ... (OS specific implementation)
  // Calculate memory usage from meminfo data
  return 0.0; // Replace with actual calculation
}

// Function to get disk usage (Cross-platform)
double getDiskUsage(const std::string& driveLetter) {
  // Implement based on your OS (e.g., using GetDiskFreeSpaceEx on Windows or statvfs on Linux)
  return 0.0; // Replace with actual calculation
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
