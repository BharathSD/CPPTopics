#include <iostream>
#include <filesystem>
#include <fstream>

/*
   File System Operations
   This section demonstrates various file system operations using the C++17 filesystem library.
   The various operations include checking file existence, iterating directories, and manipulating paths.
   The filesystem library provides a convenient and portable way to perform these operations.
   
*/
namespace fs = std::filesystem;

int main() {
    fs::path filePathToCheck = "optional.cpp";

    if (fs::exists(filePathToCheck)) {
        std::cout << filePathToCheck << " exists." << std::endl;
    } else {
        std::cout << filePathToCheck << " does not exist." << std::endl;
    }

    // iterating the directory
    // get the current file path
    fs::path dir = fs::current_path();
    if (fs::exists(dir) && fs::is_directory(dir)) {
        for (const auto& entry : fs::directory_iterator(dir)) {
            std::cout << entry.path() << std::endl;
        }
    }

    // Path manipulation examples
    fs::path newDir = dir / "new_subdirectory";
    fs::create_directory(newDir);
    std::cout << "Created directory: " << newDir << std::endl;
    fs::path fileInNewDir = newDir / "file.txt";
    std::ofstream(fileInNewDir) << "Hello, World!";
    std::cout << "Created file: " << fileInNewDir << std::endl;
    std::cout << "Created file: " << fileInNewDir << std::endl;

    // Path manipulation
    fs::path examplePath = "/home/user/file.txt";
    std::cout << examplePath.parent_path() << '\n';
    std::cout << examplePath.filename() << '\n';
    std::cout << examplePath.extension() << '\n';

    // file system library features
    fs::path currentPath = fs::current_path();
    std::cout << "Current path: " << currentPath << std::endl;

    // file size

    fs::path filePath = dir / "new_subdirectory" / "file.txt";
    if (fs::exists(filePath)) {
        std::cout << "File size: " << fs::file_size(filePath) << " bytes" << std::endl;
    }

    // file permissions
    fs::perms perms = fs::status(filePath).permissions();
    std::cout << "File permissions: ";
    std::cout << ((static_cast<unsigned>(perms) & static_cast<unsigned>(fs::perms::owner_read)) ? "r" : "-");
    std::cout << ((static_cast<unsigned>(perms) & static_cast<unsigned>(fs::perms::owner_write)) ? "w" : "-");
    std::cout << ((static_cast<unsigned>(perms) & static_cast<unsigned>(fs::perms::owner_exec)) ? "x" : "-");
    std::cout << std::endl;

    // file operations
    fs::path fileToModify = dir / "new_subdirectory" / "file.txt";
    if (fs::exists(fileToModify)) {
        std::cout << "Modifying file: " << fileToModify << std::endl;
        std::ofstream(fileToModify, std::ios::app) << "\nAppending some text.";
    }

    // file renaming
    fs::path fileToRename = dir / "new_subdirectory" / "file.txt";
    fs::path newFileName = dir / "new_subdirectory" / "renamed_file.txt";
    if (fs::exists(fileToRename)) {
        fs::rename(fileToRename, newFileName);
        std::cout << "Renamed file: " << fileToRename << " to " << newFileName << std::endl;
    }

    // file removal
    fs::path fileToRemove = dir / "new_subdirectory" / "renamed_file.txt";
    if (fs::exists(fileToRemove)) {
        fs::remove(fileToRemove);
        std::cout << "Removed file: " << fileToRemove << std::endl;
    }

    // directory removal
    fs::path dirToRemove = dir / "new_subdirectory";
    if (fs::exists(dirToRemove)) {
        fs::remove_all(dirToRemove);
        std::cout << "Removed directory: " << dirToRemove << std::endl;
    }

    return 0;
}
