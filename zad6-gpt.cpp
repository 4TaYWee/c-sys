#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

void signalHandler(int signal) {
    cout << "Received signal: " << signal << endl;
}

int main() {
    pid_t child_pid;

    // Install signal handlers
    signal(SIGSTOP, signalHandler);
    signal(SIGCONT, signalHandler);

    // Fork a child process
    child_pid = fork();

    if (child_pid < 0) {
        cerr << "Failed to fork a child process." << endl;
        return 1;
    } else if (child_pid == 0) {
        // Child process
        cout << "Child process running..." << endl;
        while (true) {
            // Child process continuously prints its PID
            cout << "Child process PID: " << getpid() << endl;
            sleep(2);
        }
    } else {
        // Parent process
        cout << "Parent process running..." << endl;
        cout << "Child process PID: " << child_pid << endl;

        // Wait for 5 seconds
        sleep(5);

        // Send SIGSTOP signal to the child process to pause it
        cout << "Pausing the child process..." << endl;
        kill(child_pid, SIGSTOP);

        // Wait for 5 seconds
        sleep(5);

        // Send SIGCONT signal to the child process to resume it
        cout << "Resuming the child process..." << endl;
        kill(child_pid, SIGCONT);

        // Wait for the child process to terminate
        waitpid(child_pid, NULL, 0);

        cout << "Child process terminated." << endl;
    }

    return 0;
}
