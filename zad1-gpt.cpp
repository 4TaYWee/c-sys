#include <iostream>
#include <fstream>

void createFile(const std::string& fileName) {
    std::ofstream file(fileName.c_str());
    if (file.is_open()) {
        std::cout << "File created successfully: " << fileName << std::endl;
        file.close();
    }
    else {
        std::cerr << "Error creating file: " << fileName << std::endl;
    }
}

int main() {
    std::string fileName;
    std::cout << "Enter the name of the file to create: ";
    std::cin >> fileName;
    createFile(fileName);
    return 0;
}
