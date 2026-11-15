
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: sigscan <directory>" << std::endl;
        return 1;
    }

    fs::path directory = argv[1];

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cout << "Directory does not exist!" << std::endl;
        return 1;
    }

    int fileCount = 0;
    uintmax_t totalSize = 0;

    std::cout << "Files in directory and subdirectories:\n";

    std::error_code error;

    for (fs::recursive_directory_iterator it(
             directory,
             fs::directory_options::skip_permission_denied
             error), end;
         it != end;
         it.increment(error)) {

        if (error) {
            error.clear();
            continue;
        }

        const auto& entry = *it;

        if (entry.is_regular_file()) {
            uintmax_t size = entry.file_size();

            std::cout << "File: " << entry.path().string()
                      << " | Size: " << size << " bytes\n";

            fileCount++;
            totalSize += size;
        }
             }

    std::cout << "\nTotal files: " << fileCount << '\n';
    std::cout << "Total size: " << totalSize << " bytes\n";

    return 0;
}
