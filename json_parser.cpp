#include <cctype>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <sstream>

#include "json_parser.hpp"

struct JsonObject {
    std::unordered_map<std::string, JsonValue> obj;
};

JsonValue parse(const std::string& json) {
    size_t i = 0;
    return parse_value(json, i);
}

JsonValue parse_value(const std::string& json, size_t& i) {
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
        std::cout << "Parsed null" << std::endl;
        return JsonValue(nullptr);
    }
    throw std::invalid_argument("Invalid JSON null");
}

JsonValue parse_true(const std::string& json, size_t& i) {
    if (json.substr(i, 4) == "true") {
        i += 4;
        std::cout << "Parsed true" << std::endl;
        return JsonValue(true);
    }
    throw std::invalid_argument("Invalid JSON true");
}

JsonValue parse_false(const std::string& json, size_t& i) {
    if (json.substr(i, 5) == "false") {
        i += 5;
        std::cout << "Parsed false" << std::endl;
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
        std::cout << "Parsed double: " << num_str << std::endl;
        return JsonValue(stod(num_str));
    } else {
        std::cout << "Parsed int: " << num_str << std::endl;
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
    std::cout << "Parsed string: " << str << std::endl;
    return JsonValue(str);
}

std::string parse_string_return_string(const std::string& json, size_t& i) {
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
    std::cout << "Parsed string: " << str << std::endl;
    return str;
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
    std::cout << "Parsed array: " << arr << std::endl;
    return JsonValue(std::move(arr));
}

JsonValue parse_object(const std::string& json, size_t& i) {
    i++; // Skip opening brace
    skip_whitespace(json, i);
    std::unordered_map<std::string, JsonValue> obj;
    while (i < json.length() && json[i] != '}') {
        if (json[i] != '"') {
            std::cerr << "Invalid JSON object key: " << json[i] << std::endl;
            throw std::invalid_argument("Invalid JSON object key");
        }

        std::string key = parse_string_return_string(json, i);
        skip_whitespace(json, i);
        if (i == json.length() || json[i] != ':') {
            throw std::invalid_argument("Missing colon in JSON object");
        }

        i++; // Skip colon
        skip_whitespace(json, i);

        obj[key] = parse_value(json, i);
        if (i < json.length() && json[i] == ',') {
            i++;
        }
        skip_whitespace(json, i);
    }
    if (i == json.length()) {
        throw std::invalid_argument("Unterminated JSON object");
    }
    i++; // Skip closing brace
    std::cout << "Parsed object: " << obj << std::endl;
    return JsonValue(std::move(obj));
}

void skip_whitespace(const std::string& json, size_t& i) {
    while (i < json.length() && std::isspace(json[i])) {
        i++;
    }
}

std::ostream& operator<<(std::ostream& os, const JsonValue& json_value) {
    std::ostringstream oss;
    std::visit([&oss](const auto& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, nullptr_t>) {
            oss << "null";
        } else if constexpr (std::is_same_v<T, bool>) {
            oss << (value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, int>) {
            oss << value;
        } else if constexpr (std::is_same_v<T, double>) {
            oss << value;
        } else if constexpr (std::is_same_v<T, std::string>) {
            oss << '"' << value << '"';
        } else if constexpr (std::is_same_v<T, std::vector<JsonValue>>) {
            oss << '[';
            bool first = true;
            for (const auto& item : value) {
                if (!first) {
                    oss << ", ";
                }
                first = false;
                oss << item;
            }
            oss << ']';
        } else if constexpr (std::is_same_v<T, std::unordered_map<std::string, JsonValue>>) {
            oss << '{';
            bool first = true;
            for (const auto& [key, val] : value) {
                if (!first) {
                    oss << ", ";
                }
                first = false;
                oss << '"' << key << "\": " << val;
            }
            oss << '}';
        }
    }, json_value.get_value());
    return os << oss.str();
}
