#include <iostream>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt"; // Change this to your file's name
    const mode_t permissions = S_IRUSR | S_IWUSR | S_IXUSR; // Example permissions: Read, Write, Execute for the file owner

    int result = chmod(filename, permissions);

    if (result == 0) {
        std::cout << "Permissions changed successfully.\n";
    } else {
        std::cerr << "Error changing permissions.\n";
    }

    return 0;
}
