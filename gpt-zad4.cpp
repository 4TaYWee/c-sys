#include <iostream>
#include <windows.h>

int main() {
    const char *filename = "example.txt"; // Change this to your file's name

    // Get the current security attributes of the file
    SECURITY_ATTRIBUTES securityAttributes;
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.lpSecurityDescriptor = NULL;
    securityAttributes.bInheritHandle = FALSE;

    // Set the desired access control information
    if (!SetFileSecurity(filename, DACL_SECURITY_INFORMATION, NULL)) {
        std::cerr << "Error clearing file permissions.\n";
        return 1;
    }

    // Alternatively, you can use SetNamedSecurityInfo() to set specific permissions

    std::cout << "File permissions changed successfully.\n";

    return 0;
}
