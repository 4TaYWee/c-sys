#include <fstream>

bool create_file(const std::string& filename) {
  std::ofstream outfile(filename);
  return outfile.is_open();
}

#include <iostream>

int main() {
  std::string filename = "new_file.txt";
  if (create_file(filename)) {
    std::cout << "File " << filename << " created successfully!" << std::endl;
  } else {
    std::cerr << "Error creating file: " << filename << std::endl;
  }
  return 0;
}
