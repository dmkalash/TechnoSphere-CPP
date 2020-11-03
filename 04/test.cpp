#include <iostream>
#include <fstream>
#include <vector>

#include "bigint.h"


constexpr int MAX_INT = +2147483647;
constexpr int MIN_INT = -2147483648;


void default_constructor_test()
{
    try {
        BigInt a;
        const BigInt b;
        if (a.as_string() != "0" || b.as_string() != "0") {
            throw "bad default constructor";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void int_constructor_test()
{
    try {
        BigInt a1(0);
        BigInt a2(1);
        BigInt a3(-1);
        BigInt a4(15);
        BigInt a5(-15);
        BigInt a6(16);
        BigInt a7(-16);
        BigInt a8(17);
        BigInt a9(-17);
        BigInt a10(MAX_INT);
        BigInt a11(MIN_INT);

        const BigInt ca1(0);
        const BigInt ca2(1);
        const BigInt ca3(-1);
        const BigInt ca4(15);
        const BigInt ca5(-15);
        const BigInt ca6(16);
        const BigInt ca7(-16);
        const BigInt ca8(17);
        const BigInt ca9(-17);
        const BigInt ca10(MAX_INT);
        const BigInt ca11(MIN_INT);


        if (a1.as_string() != "0" ||
                    a2.as_string() != "1" ||
                    a3.as_string() != "-1" ||
                    a4.as_string() != "15" ||
                    a5.as_string() != "-15" ||
                    a6.as_string() != "16" ||
                    a7.as_string() != "-16" ||
                    a8.as_string() != "17" ||
                    a9.as_string() != "-17" ||
                    a10.as_string() != std::to_string(MAX_INT) ||
                    a11.as_string() != std::to_string(MIN_INT)) {
            throw "Bad constructing and representation";
        }

        if (ca1.as_string() != "0" ||
            ca2.as_string() != "1" ||
            ca3.as_string() != "-1" ||
            ca4.as_string() != "15" ||
            ca5.as_string() != "-15" ||
            ca6.as_string() != "16" ||
            ca7.as_string() != "-16" ||
            ca8.as_string() != "17" ||
            ca9.as_string() != "-17" ||
            ca10.as_string() != std::to_string(MAX_INT) ||
            ca11.as_string() != std::to_string(MIN_INT)) {
            throw "Bad constructing and representation";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void string_constructor_test()
{
    try {
        BigInt a1("0");
        BigInt a2("1");
        BigInt a3("-1");
        BigInt a4("15");
        BigInt a5("-15");
        BigInt a6("16");
        BigInt a7("-16");
        BigInt a8("17");
        BigInt a9("-17");
        BigInt a10(std::to_string(MAX_INT));
        BigInt a11(std::to_string(MIN_INT));
        BigInt a12(std::string(20, '1'));
        BigInt a13("-" + std::string(20, '1'));
        BigInt a14("+17");
        BigInt a15("+0");
        BigInt a16("-0");
        BigInt a17("+0000000");
        BigInt a18("+00000001");
        BigInt a19("+0000000100100");
        BigInt a20("0000000000000000");
        BigInt a21("100000000000000");
        BigInt a22("1000000000000000");
        BigInt a23("10000000000000001");

        if (a1.as_string() != "0" ||
            a2.as_string() != "1" ||
            a3.as_string() != "-1" ||
            a4.as_string() != "15" ||
            a5.as_string() != "-15" ||
            a6.as_string() != "16" ||
            a7.as_string() != "-16" ||
            a8.as_string() != "17" ||
            a9.as_string() != "-17" ||
            a10.as_string() != std::to_string(MAX_INT) ||
            a11.as_string() != std::to_string(MIN_INT) ||
            a12.as_string() != std::string(20, '1') ||
            a13.as_string() != "-" + std::string(20, '1') ||
            a14.as_string() != "17" ||
            a15.as_string() != "0" ||
            a16.as_string() != "0" ||
            a17.as_string() != "0" ||
            a18.as_string() != "1" ||
            a19.as_string() != "100100" ||
            a20.as_string() != "0" ||
            a21.as_string() != "100000000000000" ||
            a22.as_string() != "1000000000000000" ||
            a23.as_string() != "10000000000000001") {
                throw "Bad constructing and representation";
        }

        const BigInt ca1("0");
        const BigInt ca2("1");
        const BigInt ca3("-1");
        const BigInt ca4("15");
        const BigInt ca5("-15");
        const BigInt ca6("16");
        const BigInt ca7("-16");
        const BigInt ca8("17");
        const BigInt ca9("-17");
        const BigInt ca10(std::to_string(MAX_INT));
        const BigInt ca11(std::to_string(MIN_INT));
        const BigInt ca12(std::string(20, '1'));
        const BigInt ca13("-" + std::string(20, '1'));
        const BigInt ca14("+17");
        const BigInt ca15("+0");
        const BigInt ca16("-0");
        const BigInt ca17("+0000000");
        const BigInt ca18("+00000001");
        const BigInt ca19("+0000000100100");
        const BigInt ca20("0000000000000000");
        const BigInt ca21("100000000000000");
        const BigInt ca22("1000000000000000");
        const BigInt ca23("10000000000000001");

        if (ca1.as_string() != "0" ||
            ca2.as_string() != "1" ||
            ca3.as_string() != "-1" ||
            ca4.as_string() != "15" ||
            ca5.as_string() != "-15" ||
            ca6.as_string() != "16" ||
            ca7.as_string() != "-16" ||
            ca8.as_string() != "17" ||
            ca9.as_string() != "-17" ||
            ca10.as_string() != std::to_string(MAX_INT) ||
            ca11.as_string() != std::to_string(MIN_INT) ||
            ca12.as_string() != std::string(20, '1') ||
            ca13.as_string() != "-" + std::string(20, '1') ||
            ca14.as_string() != "17" ||
            ca15.as_string() != "0" ||
            ca16.as_string() != "0" ||
            ca17.as_string() != "0" ||
            ca18.as_string() != "1" ||
            ca19.as_string() != "100100" ||
            ca20.as_string() != "0" ||
            ca21.as_string() != "100000000000000" ||
            ca22.as_string() != "1000000000000000" ||
            ca23.as_string() != "10000000000000001") {
            throw "Bad constructing and representation";
        }

        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void compare_test()
{
    try {
        BigInt a1, a2;
        BigInt a3(123), a4(-123), a5(123), a6(-123);
        BigInt a7("1111222233334444"), a8("+1111222233334444"), a9("-1111222233334444"), a0("-01111222233334444");
        BigInt a10(120), a11(140), a12(-120), a13(-140);

        if (a1 < a2 || a1 < a1 || a3 < a3 || a3 < a5 || a3 < a4 || a3 < a10 || a3 < a12 || a3 < a13) {
            throw "bad L comparing";
        }
        if (a7 < a8 || a7 < a9) {
            throw "bad L comparing";
        }
        if (!(a1 <= a1) || !(a3 <= a3) || !(a3 <= a5) || a3 <= a4 || a3 <= a10 || a3 <= a12 || a3 <= a13) {
            throw "bad LE comparing";
        }
        if (!(a7 <= a8) || a7 <= a9) {
            throw "bad LE compating";
        }
        if (a1 > a1 || a1 > a2 || a10 > a11 || a13 > a10 || a9 > a7) {
            throw "bad G comparing";
        }
        if (!(a1 >= a1) || !(a1 >= a2) || a4 >= a3 || !(a3 >= a5) || a12 >= a10 || a9 >= a7) {
            throw "bad GE comparing";
        }
        if (!(a1 == a1) || !(a1 == a2) || a3 == a4 || !(a3 == a5) || a7 == a9 || !(a9 == a0)) {
            throw "bad E comparing";
        }
        if (a1 != a1 || a1 != a2 || a3 != a3 || a3 != a5 || a4 != a6 || a7 != a8 || a9 != a0 || a9 != a9) {
            throw "bad NE comparing";
        }

        BigInt ca1, ca2;
        BigInt ca3(123), ca4(-123), ca5(123), ca6(-123);
        BigInt ca7("1111222233334444"), ca8("+1111222233334444"), ca9("-1111222233334444"), ca0("-01111222233334444");
        BigInt ca10(120), ca11(140), ca12(-120), ca13(-140);

        if (ca1 < ca2 || ca1 < ca1 || ca3 < ca3 || ca3 < ca5 || ca3 < ca4 || ca3 < ca10 || ca3 < ca12 || ca3 < ca13) {
            throw "bad L comparing";
        }
        if (ca7 < ca8 || ca7 < ca9) {
            throw "bad L comparing";
        }
        if (!(ca1 <= ca1) || !(ca3 <= ca3) || !(ca3 <= ca5) || ca3 <= ca4 || ca3 <= ca10 || ca3 <= ca12 || ca3 <= ca13) {
            throw "bad LE comparing";
        }
        if (!(ca7 <= ca8) || ca7 <= ca9) {
            throw "bad LE compating";
        }
        if (ca1 > ca1 || ca1 > ca2 || ca10 > ca11 || ca13 > ca10 || ca9 > ca7) {
            throw "bad G comparing";
        }
        if (!(ca1 >= ca1) || !(ca1 >= ca2) || ca4 >= ca3 || !(ca3 >= ca5) || ca12 >= ca10 || ca9 >= ca7) {
            throw "bad GE comparing";
        }
        if (!(ca1 == ca1) || !(ca1 == ca2) || ca3 == ca4 || !(ca3 == ca5) || ca7 == ca9 || !(ca9 == ca0)) {
            throw "bad E comparing";
        }
        if (ca1 != ca1 || ca1 != ca2 || ca3 != ca3 || ca3 != ca5 || ca4 != ca6 || ca7 != ca8 || ca9 != ca0 || ca9 != ca9) {
            throw "bad NE comparing";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED: Exception\n";
    }
}

void copy_constructor_test()
{
    try {
        BigInt a1, a2(0), a3(1234), a4(-1234), a5("+0001111222233334444"), a6("-001111222233334444");
        const BigInt cb1(a1), cb2(a2), cb3(a3), cb4(a4), cb5(a5), cb6(a6);
        BigInt b1(a1), b2(a2), b3(a3), b4(a4), b5(a5), b6(a6), b7(cb6);


        if (b1 != a1 || b2 != a2 || b3 != a3 || b4 != a4 || b5 != a5 || b6 != a6 || cb1 != a1 || b7 != a6) {
            throw "bad copy";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void move_constructor_test()
{
    try {
        BigInt a1, a2(0), a3(1234), a4(-1234), a5("+0001111222233334444"), a6("-001111222233334444");
        BigInt b1(a1), b2(a2), b3(a3), b4(a4), b5(a5), b6(a6);
        BigInt c1(std::move(a1)), c2(std::move(a2)), c3(std::move(a3)),
                c4(std::move(a4)), c5(std::move(a5)), c6(std::move(a6));
        if (b1 != c1 || b2 != c2 || b3 != c3 || b4 != c4 || b5 != c5 || b6 != c6) {
            throw "bad moving";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void assigment_test()
{
    try {
        BigInt a1, a2(0), a3(1234), a4(-1234), a5("+0001111222233334444"), a6("-001111222233334444");
        BigInt b1, b2, b3, b4, b5, b6, b7;
        const BigInt a7(10);
        b1 = a1, b2 = a2, b3 = a3, b4 = a4;
        b5 = b6 = a5 = a6;
        a6 = a6;
        b7 = a7;
        if (b1 != a1 || b2 != a2 || b3 != a3 || b4 != a4 || b5 != b6 || b5 != a5 || b5 != a6 || b7 != a7) {
            throw "bad assigment";
        }
        BigInt c1(1), c2(std::string(1000000, '1'));
        c1 = c2;
        if (c1 != c2) {
            throw "bad assigment";
        }
        BigInt c3(1), c4(std::string(1000000, '1'));
        c4 = c3;
        if (c3 != c4) {
            throw "bad assigment";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void move_assigment_test()
{
    try {
        BigInt a1, a2(0), a3(1234), a4(-1234), a5("+0001111222233334444"), a6("-001111222233334444");
        BigInt b1, b2, b3, b4, b5, b6;
        BigInt c1, c2(0), c3(1234), c4(-1234), c5("+0001111222233334444"), c6("-001111222233334444");
        b1 = std::move(a1);
        b2 = std::move(a2), b3 = std::move(a3), b4 = std::move(a4);
        b5 = std::move(a5);
        a6 = std::move(a6);

        if (b1 != c1 || b2 != c2 || b3 != c3 || b4 != c4 || b5 != c5 || a6 != c6) {
            throw "bad moving";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void plus_test()
{
    try {
        BigInt a1;
        BigInt a2(1), a3(1234), a4(-1234), a5("+0001111222233334444"), a6("-001111222233334444");
        BigInt a7(MAX_INT), a8(MIN_INT);
        BigInt a9("11112222333344445555"), a11("-11112222333344445555");
        BigInt a12("1" + std::string(100, '0'));
        BigInt a13("1111111111111111"), a14("1111111111111111");
        BigInt b1, b2, b3, b4, b5, b6;
        b1 = a1 + a1;
        if (b1 != a1) {
            throw "bad addition";
        }
        b2 = a1 + a2;
        if (b2 != a2) {
            throw "bad addition";
        }
        b3 = a1 + a2 + a3 + a5;
        b3 = b3 + a4 + a6;
        if (b3 != a2) {
            throw "bad addition";
        }
        b4 = a9 + a11;
        if (b4 != BigInt()) {
            throw "bad addition";
        }
        b4 = a9 + a13;
        if (b4 != (a9 + a13) || a13 + a14 != BigInt("2222222222222222")) {
            throw "bad addition";
        }
        if ((a1 + a4 != a4) || (a4 + a1 != a4) || (a3 + a4 != a1) || (a4 + a3 != a1)) {
            throw "bad addition";
        }

        const BigInt ca1(10);
        if (ca1 + a2 != BigInt(11) ||
            a2 + ca1 != BigInt(11) ||
            ca1 + ca1 != BigInt(20)) {
            throw "bad addition";
        }
        std::cout << "OK" << std::endl;
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void minus_test()
{
    try {
        BigInt a1;
        BigInt a2(1), a3(1234), a4(-1234), a5("+0001111222233334444"), a6("-001111222233334444");
        BigInt a7(MAX_INT), a8(MIN_INT);
        BigInt a9("11112222333344445555"), a11("-11112222333344445555"), a10("11110000000000000000");
        BigInt a12("1" + std::string(100, '0'));
        BigInt a13("1111111111111111"), a14("1111111111111111");
        BigInt b1, b2, b3, b4, b5, b6;
        b1 = a1 - a1;
        if (b1 != a1 || BigInt(0) - BigInt(0) != BigInt(0)) {
            throw "bad subtraction";
        }
        b2 = a1 - a2;
        if (BigInt(-1) != b2) {
            throw "bad subtraction";
        }
        b3 = a1 - a2 - a3 - a5;
        b3 = b3 - a4 - a6;
        if (b3 != a1 - a2) {
            throw "bad subtraction";
        }
        b4 = a13 - a14;
        if (b4 != BigInt()) {
            throw "bad subtraction";
        }
        b4 = a9 - a10;
        if (b4 != a9 - a10 || a9 - a10 != BigInt("2222333344445555")) {
            throw "bad subtraction";
        }
        if (BigInt("1" + std::string(40, '0')) - BigInt(1) != BigInt(std::string(40, '9'))) {
            throw "bad subtraction";
        }
        if (BigInt("1" + std::string(40, '0')) - BigInt(10) != BigInt(std::string(39, '9') + "0")) {
            throw "bad subtraction";
        }
        const BigInt ca1(10);
        if (ca1 - a2 != BigInt(9) ||
            a2 - ca1 != BigInt(-9) ||
            ca1 - ca1 != BigInt(0)) {
            throw "bad addition";
        }
        std::cout << "OK" << std::endl;
    } catch(const char *s) {
        std::cout << "FAILED: " << s << "\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void unary_minus_test()
{
    try {
        BigInt a1, a2(0), a3("+0"), a4("-0"), a5(10), a6(-10), a7(std::string(100, '1')), a8("-" + std::string(100, '1')),
                a9("+" + std::string(100, '1'));
        const BigInt ca1(10);
        if (-a1 != a1 ||
            -a2 != a1 ||
            -a3 != a1 ||
            -a4 != a1 ||
            -a5 != a6 ||
            -a6 != a5 ||
            -(-a5) != a5 ||
            -(-a6) != a6 ||
            -a7 != a8 ||
            -a8 != a7 ||
            -a5 != -a5 ||
            -a6 != -a6 ||
            -ca1 != BigInt(-10)) {
            throw "bad unary minus operation";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << std::endl;
    } catch(...) {

    }
}


void mul_test()
{
    try {
        BigInt a1, a2(0), a3(10), a4(-10), a5("+1000000000"), a6("-1000000000");
        BigInt a7("-1" + std::string(100, '0')), a8("-1" + std::string(200, '0'));
        BigInt a9(999), a10(99), a11(98901);

        //(a1 * a1).print_params();
        if (a1 * a1 != a1 ||
            a1 * a2 != a2 ||
            a1 * a3 != a1 ||
            a1 * a4 != a1 ||
            a3 * a1 != a1 ||
            a4 * a1 != a1 ||
            a1 * a8 != a1 ||
            a8 * a1 != a1) {
            throw "bad multiplication";
        }
        if (a3 * a4 != BigInt(-100) ||
            a4 * a3 != BigInt(-100) ||
            a3 * a3 != BigInt(100) ||
            a4 * a4 != BigInt(100) ||
            a5 * a6 != BigInt("-1" + std::string(18, '0'))) {
            throw "bad multiplication";
        }
        if (a7 * a8 != BigInt("1" + std::string(300, '0')) ||
            a8 * a7 != BigInt("1" + std::string(300, '0'))) {
            throw "bad multiplication";
        }
        BigInt b1 = a10 * a10;
        if (a9 * a10 != a11 ||
            a10 * a9 != a11 ||
            b1 != BigInt(9801) ||
            a10 * a11 != BigInt(9791199) ||
            a11 * a10 != BigInt(9791199)) {
            throw "bad multiplication";
        }

        const BigInt ca9(999), ca10(99), ca11(98901);
        if (ca9 * ca10 != ca11 ||
            ca10 * ca9 != ca11 ||
            ca10 * ca11 != BigInt(9791199) ||
            ca11 * ca10 != BigInt(9791199)) {
            throw "bad multiplication";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << std::endl;
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void output_test()
{
    try {
        std::ofstream fout("output.txt");
        BigInt a1, a2(0), a3(10), a4(-10), a5("+1000000000"), a6("-1000000000");
        BigInt a7("1" + std::string(100, '0')), a8("-1" + std::string(200, '0'));
        BigInt a9("+1" + std::string(100, '0')), a10("-" + std::string(150, '0'));
        std::vector<BigInt> arr = {a1, a2, a3, a4, a5, a6, a7, a8, a9, a10};
        std::vector<std::string> ans(arr.size());
        for (int i = 0; i < arr.size(); i++) {
            fout << arr[i] << " ";
            ans[i] = arr[i].as_string();
        }
        const BigInt ca1(-10);
        fout << ca1 << " ";

        fout.close();

        std::string s;
        std::ifstream fin("output.txt");
        for (int i = 0; i < arr.size(); i++) {
            fin >> s;
            if (s != ans[i]) {
                fin.close();
                throw "bad output";
            }
        }
        fin >> s;
        if (s != ca1.as_string()) {
            throw "bad output";
        }
        std::cout << "OK\n";
    } catch(const char *s) {
        std::cout << "FAILED: " << s << std::endl;
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


int main()
{
    default_constructor_test();
    int_constructor_test();
    string_constructor_test();
    compare_test();
    copy_constructor_test();
    move_constructor_test();
    assigment_test();
    move_assigment_test();
    unary_minus_test();
    plus_test();
    minus_test();
    mul_test();
    output_test();
    return 0;
}
