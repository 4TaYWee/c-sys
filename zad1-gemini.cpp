#include <fstream>
#include <iostream>

bool create_file(const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile.close();
        return true;
    }
    else {
        std::cerr << "Error creating file: " << filename << std::endl;
        return false;
    }
}


int main() {
    std::string filename = "new_fisle.txt";
    if (create_file(filename)) {
        std::cout << "File '" << filename << "' created successfully!" << std::endl;
    }
    else {
        std::cerr << "Failed to create file." << std::endl;
    }
    return 0;
}
