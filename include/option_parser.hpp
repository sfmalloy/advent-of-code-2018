#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>

const int INT_NOT_FOUND = INT32_MIN;
const std::string STR_NOT_FOUND = "";

class option_parser 
{
public:
    // Default ctor: not used as there's no point in parsing nothing
    option_parser() = delete;
    
    // Ctor: taking in argc and argv from main
    option_parser(int argc, char* argv[]);

    // Dtor
    ~option_parser();

    // Get the argument value as a string
    std::string
    get_str(const std::string& arg_name);

    // Get the argument as an int
    int
    get_int(const std::string& arg_name);

    bool
    has(const std::string& arg_name);

private:
    std::vector<char*> m_raw_args;
    std::unordered_map<std::string, std::string> m_args;
};
