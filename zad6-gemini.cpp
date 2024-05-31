#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int pid = fork();

  // Error handling for fork
  if (pid < 0) {
    std::cerr << "Error creating child process" << std::endl;
    return 1;
  } else if (pid == 0) {
    // Child process
    std::cout << "Child process started (PID: " << getpid() << ")" << std::endl;
    // Replace this with the actual program you want to execute
    execlp("ls", "ls", "-l", "/", NULL);
    // If exec fails, original code continues here (unlikely)
    std::cerr << "Error executing program" << std::endl;
  } else {
    // Parent process
    std::cout << "Parent process waiting for child (PID: " << pid << ")" << std::endl;
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      std::cout << "Child process exited with status: " << WEXITSTATUS(status) << std::endl;
    } else {
      std::cerr << "Child process terminated abnormally" << std::endl;
    }
  }

  return 0;
}
