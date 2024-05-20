// Write a json parser that can parse the following json string:
// {
//    "name": "John",
//    "age": 30,
//    "cars": {
//    "car1": "Ford",
//    "car2": "BMW",
//    "car3": "Fiat"
//    }
//    "friends": ["Jane", "Jack", "Philip"]
//    "isMarried": true
//    "spouse": null
//    "children": []
//    "address": {
//    "street": "123 Main Street",
//    "city": "New York",
//    "state": "NY",
//    "zip": "10001"
//    }
//    "phoneNumbers": [
//    {
//    "type": "home",
//    "number": "212 555-1234"
//    },
//    {
//    "type": "office",
//    "number": "646 555-4567"
//    }
//    ]
// }

#include <iostream>
#include <fstream>

#include <getopt.h>

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

    std::cout << "Parsing json object: " << json_file << std::endl;

    return 0;
}
