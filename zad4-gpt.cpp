#include <iostream>
#include <fstream>

void copyFile(const std::string& sourceFileName, const std::string& destinationFileName) {
    std::ifstream sourceFile(sourceFileName, std::ios::binary);
    std::ofstream destinationFile(destinationFileName, std::ios::binary);

    if (!sourceFile.is_open()) {
        std::cerr << "Error opening source file: " << sourceFileName << std::endl;
        return;
    }

    if (!destinationFile.is_open()) {
        std::cerr << "Error opening destination file: " << destinationFileName << std::endl;
        return;
    }

    destinationFile << sourceFile.rdbuf();

    sourceFile.close();
    destinationFile.close();

    std::cout << "File copied successfully from " << sourceFileName << " to " << destinationFileName << std::endl;
}

int main() {
    std::string sourceFileName = "source.txt";
    std::string destinationFileName = "destination.txt";

    copyFile(sourceFileName, destinationFileName);

    return 0;
}
