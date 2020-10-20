#pragma once
#include <functional>
#include <vector>

class Parser {
    std::function<void(std::string &text)> start_callback;
    std::function<void(std::string &text)> end_callback;
    std::function<std::string (std::string &)> digit_token_callback;
    std::function<std::string (std::string &)> string_token_callback;
public:
    Parser();
    void set_start_callback(const std::function<void(std::string &text)> &);
    void set_end_callback(const std::function<void(std::string &text)> &);
    void set_digit_token_callback(const std::function<std::string (std::string &)> &);
    void set_string_token_callback(const std::function<std::string (std::string &)> &);
    std::vector<std::string> token_parser(const std::string &text);
};
