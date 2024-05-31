#include <iostream>
#include <experimental/filesystem>

int main() {
  // Replace with the actual path to your file
  const std::filesystem::path path = "/home/kali/Desktop/New Folder/plik";

  // Set the desired permissions (octal format)
  mode_t permissions = 0644;  // Owner: rw-, Group: r--, Others: r--

  try {
    // Convert permission mask to std::filesystem::perms object
    std::experimental::filesystem::perms desired_perms = static_cast<std::experimental::filesystem::perms>(permissions);

    std::filesystem::permissions(path, desired_perms);
    std::cout << "File permissions for '" << path << "' changed successfully to "
              << std::oct << permissions << std::endl;
  } catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
