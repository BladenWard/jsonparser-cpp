#include <cctype>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "json_parser.hpp"

struct JsonObject {
    std::unordered_map<std::string, JsonValue> obj;
};

JsonValue parse(const std::string& json) {
    size_t i = 0;
    return parse_value(json, i);
}

JsonValue parse_value(const std::string& json, size_t& i) {
    std::cout << "Parsing value: " << json[i] << std::endl;
    switch (json[i]) {
        case 'n':
            return parse_null(json, i);
        case 't':
            return parse_true(json, i);
        case 'f':
            return parse_false(json, i);
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return parse_number(json, i);
        case '"':
            return parse_string(json, i);
        case '[':
            return parse_array(json, i);
        case '{':
            return parse_object(json, i);
        default:
            throw std::invalid_argument("Invalid JSON value");
    }
}

JsonValue parse_null(const std::string& json, size_t& i) {
    if (json.substr(i, 4) == "null") {
        i += 4;
        return JsonValue(nullptr);
    }
    throw std::invalid_argument("Invalid JSON null");
}

JsonValue parse_true(const std::string& json, size_t& i) {
    if (json.substr(i, 4) == "true") {
        i += 4;
        return JsonValue(true);
    }
    throw std::invalid_argument("Invalid JSON true");
}

JsonValue parse_false(const std::string& json, size_t& i) {
    if (json.substr(i, 5) == "false") {
        i += 5;
        return JsonValue(false);
    }
    throw std::invalid_argument("Invalid JSON false");
}

JsonValue parse_number(const std::string& json, size_t& i) {
    size_t start = i;
    bool is_double = false;
    while (i < json.length() && (isdigit(json[i]) || json[i] == '.' || json[i] == 'e' || json[i] == 'E' || json[i] == '+' || json[i] == '-')) {
        if (json[i] == '.') {
            is_double = true;
        }
        i++;
    }
    std::string num_str = json.substr(start, i - start);
    if (is_double) {
        return JsonValue(stod(num_str));
    } else {
        return JsonValue(stoi(num_str));
    }
}

JsonValue parse_string(const std::string& json, size_t& i) {
    i++; // Skip opening quote
    size_t start = i;
    while (i < json.length() && json[i] != '"') {
        if (json[i] == '\\') {
            i++; // Skip escaped character
        }
        i++;
    }
    if (i == json.length()) {
        throw std::invalid_argument("Unterminated JSON std::string");
    }
    std::string str = json.substr(start, i - start);
    i++; // Skip closing quote
    std::cout << "Parsed std::string: " << str << std::endl;
    return JsonValue(str);
}

JsonValue parse_array(const std::string& json, size_t& i) {
    i++; // Skip opening bracket
    skip_whitespace(json, i);
    std::vector<JsonValue> arr;
    while (i < json.length() && json[i] != ']') {
        arr.push_back(parse_value(json, i));
        if (i < json.length() && json[i] == ',') {
            i++;
        }
        skip_whitespace(json, i);
    }
    if (i == json.length()) {
        throw std::invalid_argument("Unterminated JSON array");
    }
    i++; // Skip closing bracket
    return JsonValue(std::move(arr));
}

JsonValue parse_object(const std::string& json, size_t& i) {
    i++; // Skip opening brace
    std::unordered_map<std::string, JsonValue> obj;
    while (i < json.length() && json[i] != '}') {
        if (json[i] != '"') {
            std::cerr << "Invalid JSON object key: " << json[i] << std::endl;
            throw std::invalid_argument("Invalid JSON object key");
        }
        i++; // Skip opening quote
        size_t start = i;
        while (i < json.length() && json[i] != '"') {
            if (json[i] == '\\') {
                i++; // Skip escaped character
            }
            i++;
        }
        if (i == json.length()) {
            throw std::invalid_argument("Unterminated JSON std::string");
        }
        std::string key = json.substr(start, i - start);
        i++; // Skip closing quote
        if (i == json.length() || json[i] != ':') {
            throw std::invalid_argument("Missing colon in JSON object");
        }
        i++; // Skip colon
        obj[key] = parse_value(json, i);
        if (i < json.length() && json[i] == ',') {
            i++;
        }
    }
    if (i == json.length()) {
        throw std::invalid_argument("Unterminated JSON object");
    }
    i++; // Skip closing brace
    return JsonValue(std::move(obj));
}

void skip_whitespace(const std::string& json, size_t& i) {
    while (i < json.length() && std::isspace(json[i])) {
        i++;
    }
}
