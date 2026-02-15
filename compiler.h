#pragma once
#include <string>
#include <ranges>
#include <vector>
#include <iostream>
#include <cstdint>
#include <string_view>

inline constexpr std::string_view ONLY_KEYWORD = "SHEEP";
std::vector<std::string> split(std::string_view str, char delim);
std::string replace_all(std::string str, const std::string& from, const std::string& to);
std::string join(const std::vector<std::string>& vec, const std::string& delimiter);
std::vector<std::uint8_t> bitstring_to_bytes(const std::string& bitstring);
std::vector<std::uint8_t> compile(const std::string& source);
std::string bytes_to_bitstring(const std::vector<std::uint8_t>& bytes);
std::string decompile(const std::vector<std::uint8_t>& bytecode);
