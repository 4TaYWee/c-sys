#include <iostream>
#include <filesystem>

bool copy_file(const std::string& source, const std::string& destination) {
  try {
    std::filesystem::copy(source, destination);
    return true;
  } catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "Error copying file: " << e.what() << std::endl;
    return false;
  }
}

int main() {
  if (copy_file("source.txt", "copy.txt")) {
    std::cout << "File copied successfully!" << std::endl;
  }
  return 0;
}
