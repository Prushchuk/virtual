#include <iostream>
#include <fstream>
#include <bitset>

class FileHandler {
public:
    virtual void Display(const char* path) {
        std::ifstream file(path);
        if (file.is_open()) {
            char character;
            while (file.get(character)) {
                std::cout << character;
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << path << std::endl;
        }
    }
};

class AsciiFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (file.is_open()) {
            int character;
            while ((character = file.get()) != EOF) {
                std::cout << character << " ";
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << path << std::endl;
        }
    }
};

class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path, std::ios::binary);
        if (file.is_open()) {
            unsigned char byte;
            while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
                std::cout << std::bitset<8>(byte) << " ";
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << path << std::endl;
        }
    }
};

int main() {
    const char* filename = "example.txt";

    FileHandler fileHandler;
    std::cout << "Displaying file using base class:" << std::endl;
    fileHandler.Display(filename);

    AsciiFileHandler asciiHandler;
    std::cout << "\n\nDisplaying file using ASCII file handler:" << std::endl;

    BinaryFileHandler binaryHandler;
    std::cout << "\n\nDisplaying file using Binary file handler:" << std::endl;
    binaryHandler.Display(filename);
}