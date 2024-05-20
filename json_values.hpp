#ifndef JSON_VALUES_HPP
#define JSON_VALUES_HPP

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

class JsonValue {
public:
    using value_type = std::variant<std::string, int, double, bool, std::nullptr_t, std::vector<JsonValue>, std::unordered_map<std::string, JsonValue>>;

    JsonValue() : value_(nullptr) {}
    JsonValue(nullptr_t) : value_(nullptr) {}
    JsonValue(bool b) : value_(b) {}
    JsonValue(int i) : value_(i) {}
    JsonValue(double d) : value_(d) {}
    JsonValue(const std::string& s) : value_(s) {}
    JsonValue(std::vector<JsonValue> v) : value_(v) {}
    JsonValue(std::unordered_map<std::string, JsonValue> m) : value_(m) {}

    value_type& get_value() { return value_; }
    const value_type& get_value() const { return value_; }

private:
    value_type value_;
};

#endif
