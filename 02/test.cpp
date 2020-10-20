#include <iostream>
#include <functional>
#include "parser.h"


void creating_parser_object_test();
void set_start_callback_test();
void set_end_callback_test();
void set_digit_token_callback_test();
void set_string_token_callback_test();
void default_token_parser_test();
void specified_token_parser_test();
void empty_token_parser_test();
void space_token_parser_test();
void digit_token_parser_test();
void string_token_parser_test();
void lambda_token_parser_test();
void pointer_token_parser_test();
void func_token_parser_test();


void creating_parser_object_test() {
    try {
        Parser prs;
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void set_start_callback_test() {
    try {
        Parser prs;
        prs.set_start_callback([](std::string &s) {s += "_start";});
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void set_end_callback_test() {
    try {
        Parser prs;
        prs.set_end_callback([](std::string &s) {s += "_end";});
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void set_digit_token_callback_test() {
    try {
        Parser prs;
        prs.set_digit_token_callback([](std::string &s) {return s + "0";});
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void set_string_token_callback_test() {
    try {
        Parser prs;
        prs.set_string_token_callback([](std::string &s) {s = "test_" + s; return s;});
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void default_token_parser_test() {
    try {
        Parser prs;
        std::vector<std::string> out = prs.token_parser(" i  wanna \n 10 times test this \t 7th function 7");
        std::vector<std::string> ans = {"i", "wanna", "10", "times", "test", "this", "7th", "function", "7"};
        if (out != ans) {
            throw -1;
        }
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void specified_token_parser_test() {
    try {
        Parser prs;

        prs.set_start_callback([](std::string &s) {s = "START " + s;});
        prs.set_end_callback([](std::string &s) {s.clear();});
        prs.set_digit_token_callback([](std::string &s) {s = "<" + std::to_string(std::stoi(s) * 10) + ">"; return s;});
        prs.set_string_token_callback([](std::string &s) {s = "<" + s + ">"; return s;});

        std::vector<std::string> out = prs.token_parser("now i   wanna \n 10 times test this \t 7th function 7\n\n\n");
        std::vector<std::string> ans = {"<START>", "<now>", "<i>", "<wanna>", "<100>", "<times>", "<test>", "<this>",
                                        "<7th>", "<function>", "<70>"};
        if (out != ans) {
            throw -3;
        }
        std::cout << "OK" << std::endl;
    }
    catch(int) {
        std::cout << "FAILED" << std::endl;
    }
    catch(...) {
        std::cout << "ERROR" << std::endl;
    }
}


void empty_token_parser_test() {
    try {
        Parser prs;
        std::vector<std::string> out = prs.token_parser("");
        std::vector<std::string> ans = {};
        if (out != ans) {
            throw -1;
        }
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void space_token_parser_test() {
    try {
        Parser prs;
        std::vector<std::string> out = prs.token_parser("   \t   \n        \n");
        std::vector<std::string> ans = {};
        if (out != ans) {
            throw -1;
        }
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void digit_token_parser_test() {
    try {
        Parser prs;
        std::vector<std::string> out = prs.token_parser(" 1 11 111 111111");
        std::vector<std::string> ans = {"1", "11", "111", "111111"};
        if (out != ans) {
            throw -1;
        }
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void string_token_parser_test() {
    try {
        Parser prs;
        std::vector<std::string> out = prs.token_parser("a aa aaa aaaa");
        std::vector<std::string> ans = {"a", "aa", "aaa", "aaaa"};
        if (out != ans) {
            throw -1;
        }
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void lambda_token_parser_test() {
    try {
        Parser prs;

        prs.set_start_callback([](std::string &s) {s[0] = '!';});
        prs.set_end_callback([](std::string &s) {s.clear();});
        prs.set_digit_token_callback([](std::string &s) {return std::to_string(std::stoi(s) - 2);});
        prs.set_string_token_callback([](std::string &s) {s[0] = toupper(s[0]); return s;});

        std::vector<std::string> out = prs.token_parser(" i  wanna \n 10 times test this \t 7th function 7");
        std::vector<std::string> ans = {"!i", "Wanna", "8", "Times", "Test", "This", "7th", "Function", "5"};
        if (out != ans) {
            throw -1;
        }
        std::cout << "OK" << std::endl;

        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void f1(std::string &s) {s[0] = '!';}
std::string f2(std::string &s) {return std::to_string(std::stoi(s) - 2);}
std::string f3(std::string &s) {s[0] = toupper(s[0]); return s;}

void pointer_token_parser_test() {
    try {
        Parser prs;

        prs.set_start_callback(f1);
        prs.set_end_callback(f1);
        prs.set_digit_token_callback(f2);
        prs.set_string_token_callback(f3);

        std::vector<std::string> out = prs.token_parser(" i  wanna \n 10 times test this \t 7th function 7");
        std::vector<std::string> ans = {"!i", "Wanna", "8", "Times", "Test", "This", "7th", "Function", "5"};
        if (out != ans) {
            throw -1;
        }

        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }
}


void func_token_parser_test() {
    try {
        Parser prs;

        std::function<void(std::string &s)> p1 = f1;
        std::function<void(std::string &s)> p2 = f1;
        std::function<std::string (std::string &s)> p3 = f2;
        std::function<std::string (std::string &s)> p4 = f3;

        prs.set_start_callback(p1);
        prs.set_end_callback(p2);
        prs.set_digit_token_callback(p3);
        prs.set_string_token_callback(p4);

        std::vector<std::string> out = prs.token_parser(" i  wanna \n 10 times test this \t 7th function 7");
        std::vector<std::string> ans = {"!i", "Wanna", "8", "Times", "Test", "This", "7th", "Function", "5"};

        if (out != ans) {
            throw -1;
        }
        std::cout << "OK" << std::endl;
    }
    catch(...) {
        std::cout << "FAILED" << std::endl;
    }

}


int main() {
    creating_parser_object_test();
    set_start_callback_test();
    set_end_callback_test();
    set_digit_token_callback_test();
    set_string_token_callback_test();
    default_token_parser_test();
    specified_token_parser_test();
    empty_token_parser_test();
    space_token_parser_test();
    digit_token_parser_test();
    string_token_parser_test();
    lambda_token_parser_test();
    pointer_token_parser_test();
    func_token_parser_test();
}
