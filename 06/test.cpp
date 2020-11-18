#include <iostream>
#include <exception>
#include "format.hpp"
#include <string>


using namespace Format;


void default_format_test()
{
    try {
        auto text1 = format("this is {0} number", 2);
        if (text1 != "this is 2 number") {
            throw -1;
        }
        auto text2 = format("this is {0} number", true);
        if (text2 != "this is 1 number") {
            throw -1;
        }
        auto text3 = format("this is {0} number", "four");
        if (text3 != "this is four number") {
            throw -1;
        }
        auto text4 = format("this is {0} number", 2.5);
        if (text4 != "this is 2.5 number") {
            throw -1;
        }
        auto text5 = format("this is {0} number", -20);
        if (text5 != "this is -20 number") {
            throw -1;
        }
        auto text6 = format("{0}this is number{1}", '<', '>');
        if (text6 != "<this is number>") {
            throw -1;
        }
        auto text7 = format("this is {0}{1} number", 10, 20);
        if (text7 != "this is 1020 number") {
            throw -1;
        }
        auto text8 = format("this is {1}{0} number", 10, 20);
        if (text8 != "this is 2010 number") {
            throw -1;
        }
        auto text9 = format("{1}this is {2} number{0}", '!', "-", 7);
        if (text9 != "-this is 7 number!") {
            throw -1;
        }
        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void specified_format_test()
{
    try {
        auto text1 = format("{0}", 200);
        if (text1 != "200") {
            throw -1;
        }
        auto text2 = format("{1}{0}{2}", 1, 2, '3');
        if (text2 != "213") {
            throw -1;
        }
        auto text3 = format("{0}{02}{004}", 1, 2, 3, 4, 5, 6);
        if (text3 != "135") {
            throw -1;
        }
        auto text4 = format("{0}{0}{0}", 1, 2, 3);
        if (text4 != "111") {
            throw -1;
        }
        auto text5 = format("{0}", "");
        if (text5 != "") {
            throw -1;
        }
        auto text6 = format("{1}{1}", '<', '>');
        if (text6 != ">>") {
            throw -1;
        }
        auto text7 = format("{0}-{1}-{2}", "{1}", "{2}", "{3}");
        if (text7 != "{1}-{2}-{3}") {
            throw -1;
        }
        auto text8 = format("{0}{1}{0}", 10, 20);
        if (text8 != "102010") {
            throw -1;
        }
        auto text9 = format("print", 10, 20);
        if (text9 != "print") {
            throw -1;
        }
        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void errors_format_test()
{
    try {
        std::string text;

        try {
            text = format("{-1}", 200);
        } catch(const KeyError &e) {}

        try {
            text = format("{+0}", 1);
        } catch(const KeyError &e) {}

        try {
            text = format("{-}", 1);
        } catch(const KeyError &e) {
            if (std::string(e.what()) != std::string("keyerror")) {
                throw -1;
            }
        }

        try {
            text = format("{}", 1, 2, 3);
        } catch(const KeyError &e) {}

        try {
            text = format("{0}{1}{2}{3}", 1, 2, 3);
        } catch(const IndexError &e) {}

        try {
            text = format("{3}", 1, 2, 3);
        } catch(const IndexError &e) {}

        try {
            text = format("{10000000}", 1);
        } catch(const IndexError &e) {}

        try {
            text = format("{0}");
        } catch(const IndexError &e) {}

        try {
            text = format("{1-1}");
        } catch(const KeyError &e) {}

        try {
            text = format("{0}tex{t", 1, 2, 3);
        } catch(const ValueError &e) {}

        try {
            text = format("{0}tex}t", 1, 2, 3);
        } catch(const ValueError &e) {}

        try {
            text = format("{0}tex{0", 1, 2, 3);
        } catch(const ValueError &e) {}

        try {
            text = format("{0}tex}0", 1, 2, 3);
        } catch(const ValueError &e) {}

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


int main()
{
    default_format_test();
    specified_format_test();
    errors_format_test();
    return 0;
}
