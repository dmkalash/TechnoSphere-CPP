#include <string>
#include "parser.h"


Parser::Parser() {
    this->start_callback = [](std::string &text) {};
    this->end_callback = [](std::string &text) {};
    this->digit_token_callback = [](std::string &arg) {return arg;};
    this->string_token_callback = [](std::string &arg) {return arg;};
}

void Parser::set_start_callback(const std::function<void(std::string &)> &f) {
    this->start_callback = f;
}


void Parser::set_end_callback(const std::function<void(std::string &)> &f)  {
    this->end_callback = f;
}


void Parser::set_digit_token_callback(const std::function<std::string (std::string &)> &f)  {
    this->digit_token_callback = f;
}


void Parser::set_string_token_callback(const std::function<std::string (std::string &)> &f)  {
    this->string_token_callback = f;
}


std::vector<std::string> Parser::token_parser(const std::string &t_text) {
    std::vector<std::string> result;

    std::string text(t_text);
    this->start_callback(text);

    size_t i = 0;
    std::string cur_token;
    while (i < text.size()) {
        while (i < text.size() && isspace(text[i])) {
            ++i;
        }
        if (i == text.size()) {
            break;
        }
        bool non_digit = false;
        std::string token;
        while (i < text.size() && !isspace(text[i])) {
            token += text[i];
            if (!isdigit(text[i])) {
                non_digit = true;
            }
            ++i;
        }
        if (non_digit) {
            result.push_back(this->string_token_callback(token));
        } else {
            result.push_back(this->digit_token_callback(token));
        }
    }

    this->end_callback(text);
    return result;
}
