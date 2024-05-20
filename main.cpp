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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <json_object>" << std::endl;
        return 1;
    }

    int opt;
    std::string json_file;
    std::string json_object;
    while ((opt = getopt(argc, argv, "f:h")) != -1) {
        switch (opt) {
            case 'f':
                {
                    // TODO: make fp for reading stdin
                    std::ifstream file(optarg);
                    std::cout << "Reading json file: " << optarg << std::endl;
                    if (!file) {
                        std::cerr << "Error: could not open file: " << optarg << std::endl;
                        return 1;
                    }
                    while (file) {
                        std::string line;
                        std::getline(file, line);
                        json_file += line;
                    }
                    break;
                }
            default:
                std::cout << "Usage: " << argv[0] << " -f <json_file>" << std::endl;
                return 0;
        }
    }

    return 0;
}
