#include <cstdlib>
#include <iostream>

int main() {
  // Replace "ls -l" with the desired system command
  const char* command = "ls -l";

  // Attempt to execute the command
  int result = std::system(command);

  // Check the return value for success or failure
  if (result == 0) {
    std::cout << "Command '" << command << "' executed successfully." << std::endl;
  } else {
    std::cerr << "Error executing command '" << command << "'. Return value: " << result << std::endl;
  }

  return 0;
}
