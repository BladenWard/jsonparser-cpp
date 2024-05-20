#include <iostream>
#include <fstream>
#include <string>

#include <getopt.h>

#include "json_parser.hpp"

std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::string json_file;
    if (!file) {
        std::cerr << "Error: could not open file: " << filename << std::endl;
        exit(1);
    }

    while (file) {
        std::string line;
        std::getline(file, line);
        json_file += line;
    }

    return json_file;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <json_object>" << std::endl;
        return 1;
    }

    FILE* fp;  // this is for redirecting stdin
    int opt;
    std::string json_file = argv[1];

    while ((opt = getopt(argc, argv, "f:h")) != -1) {
        switch (opt) {
            case 'f':
                json_file = read_file(optarg);
                break;
            default:
                std::cout << "Usage: " << argv[0] << " -f <json_file>" << std::endl;
                return 0;
        }
    }

    parse(json_file);

    return 0;
}
