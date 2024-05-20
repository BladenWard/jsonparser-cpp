#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include "json_values.hpp"

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

#endif
