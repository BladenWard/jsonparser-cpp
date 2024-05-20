#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <iostream>
#include <cctype>
#include <ostream>

#include "json_values.hpp"

std::string trim(const std::string& str);
JsonValue parse(const std::string& value);
JsonValue parse_value(const std::string& value, size_t& i);
JsonValue parse_string(const std::string& value, size_t& i);
JsonValue parse_number(const std::string& value, size_t& i);
JsonValue parse_true(const std::string& value, size_t& i);
JsonValue parse_false(const std::string& value, size_t& i);
JsonValue parse_null(const std::string& value, size_t& i);
JsonValue parse_array(const std::string& value, size_t& i);
JsonValue parse_object(const std::string& value, size_t& i);
void skip_whitespace(const std::string& value, size_t& i);
void print_json(const JsonValue& value);
std::ostream& operator<<(std::ostream& os, const JsonValue& json_value);

#endif
