#include <iostream>
#include <cstdlib> // for system()
#include <chrono> // for timing

int main() {
    // Command to print system time in Windows
    const char* command = "time /t";
    // Execute the command
    int returnCode = system(command);

    // Check if the command was executed successfully
    if (returnCode == 0) {
        std::cout << "Command executed successfully.\n";
    } else {
        std::cerr << "Command failed to execute.\n";
    }

    return 0;
}
