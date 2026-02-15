#include "compiler.h"
#include <string>
#include <ranges>
#include <vector>
#include <iostream>
#include <cstdint>
#include <string_view>

std::vector<std::string> split(std::string_view str, char delim) {
    std::vector<std::string> result;

    for (auto part : str | std::views::split(delim)) {
        result.emplace_back(part.begin(), part.end());
    }

    return result;
}

std::string replace_all(std::string str,
                        const std::string& from,
                        const std::string& to)
{
    if (from.empty()) return str;

    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }

    return str;
}

std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
    if (vec.empty()) return "";

    std::string result = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        result += delimiter;
        result += vec[i];
    }
    return result;
}

std::vector<std::uint8_t> bitstring_to_bytes(const std::string& bitstring) {
    std::vector<std::uint8_t> bytes;
    for (size_t i = 0; i < bitstring.size(); i += 8) {
        std::string byte_str = bitstring.substr(i, 8);
        std::uint8_t byte = 0;
        for (size_t j = 0; j < byte_str.size(); ++j) {
            byte <<= 1;
            if (byte_str[j] == '1') {
                byte |= 1;
            }
        }
        bytes.push_back(byte);
    }
    return bytes;
}

std::vector<std::uint8_t> compile(const std::string& source) {
    std::string code = source;
    std::vector<std::string> lines = split(code, '\n');
    code = replace_all(code, "\n", " \n ");
    std::vector<std::string> tokens = split(code, ' ');
    std::string bitcode;
    std::string error;
    long long error_count = 0;
    long long line = 1;
    long long col = 1;
    for (const std::string& token : tokens) {
        if (token == ONLY_KEYWORD) {
            bitcode += '1';
            col += ONLY_KEYWORD.size();
            col++;
        } else if (token == "\n") {
            bitcode += '0';
            line++;
            col = 1;
        } else if (token.empty()) {
            col++;
        } else {
            error += "Unexpected token '" + token + "' at line " + std::to_string(line) + ", column " + std::to_string(col) + "\n";
            error += "  " + lines[line - 1] + "\n";
            error += std::string(col - 1, ' ') + std::string(token.size(), '^') + "\n";
            error_count++;
            col += token.size();
            col++;
        }
    }
    if (bitcode.size() % 8 != 0) {
        bitcode += std::string(8 - (bitcode.size() % 8), '0');
    }
    if (!error.empty()) {
        std::cerr << "Compilation failed with " << error_count << " error(s):\n" << error;
        return {};
    }
    std::vector<std::uint8_t> bytes = bitstring_to_bytes(bitcode);
    return bytes;
}

std::string bytes_to_bitstring(const std::vector<std::uint8_t>& bytes) {
    std::string bitstring;
    for (std::uint8_t byte : bytes) {
        for (int i = 7; i >= 0; --i) {
            bitstring += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    return bitstring;
}

std::string decompile(const std::vector<std::uint8_t>& bytes) {
    std::string bitstring = bytes_to_bitstring(bytes);
    std::string source = replace_all(bitstring, "1", std::string(ONLY_KEYWORD) + " ");
    source = replace_all(source, "0", "\n");
    std::vector<std::string> lines = split(source, '\n');
    std::string result;
    for (const std::string& line : lines) {
        if (!line.empty()) {
            if (line.back() == ' ') {
                result += line.substr(0, line.size() - 1) + "\n";
            } else {
                result += line + "\n";
            }
        } else {
            result += "\n";
        }
    }
    return result.substr(0, result.size() - 1);
}
