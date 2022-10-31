#include <exception>
#include <iostream>
#include <stdexcept>

#include "option_parser.hpp"

option_parser::option_parser(int argc, char* argv[])
    : m_raw_args(argv + 1, argv + argc),
      m_args()
{
    for (int i = 0; i < argc - 1; i += 2) 
    {
        std::string arg_name(m_raw_args[i]);
        if (arg_name[0] == '-')
            arg_name = arg_name.substr(1);
        if (i + 1 == argc - 1)
        {
            std::cerr << "Missing argument for flag -" << arg_name << '\n';
            exit(-1);
        }
        m_args[arg_name] = std::string(m_raw_args[i + 1]);
    }
}

option_parser::~option_parser() { }

std::string 
option_parser::get_str(const std::string& arg_name)
{
    if (m_args.find(arg_name) != std::end(m_args))
        return m_args.at(arg_name);
    return STR_NOT_FOUND;
}

int
option_parser::get_int(const std::string& arg_name)
{
    if (m_args.find(arg_name) != std::end(m_args))
    {
        try 
        {
            return std::stoi(m_args.at(arg_name));
        } 
        catch (std::invalid_argument e) 
        {
            std::cerr << "Expected number, got \'" << m_args.at(arg_name) << "\' instead" << '\n';
        }

    }
    return INT_NOT_FOUND;
}
