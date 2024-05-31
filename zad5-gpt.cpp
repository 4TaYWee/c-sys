#include <iostream>
#include <cstdlib> // for system()
#include <chrono> // for timing

int main() {
    // Command to print system time in Windows
    const char* command = "time /t";

    // Start the timer
    auto start = std::chrono::steady_clock::now();

    // Execute the command
    int returnCode = system(command);

    // Stop the timer
    auto end = std::chrono::steady_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Check if the command was executed successfully
    if (returnCode == 0) {
        std::cout << "Command executed successfully.\n";
        std::cout << "Time taken: " << duration.count() << " milliseconds\n";
    } else {
        std::cerr << "Command failed to execute.\n";
    }

    return 0;
}
