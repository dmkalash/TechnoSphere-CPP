#include <iostream>
#include <fstream>

#include "matrix.h"


void matrix_default_creating_test() {
    try {
        Matrix a(10, 10);
        Matrix b(1, 10);
        Matrix c(10, 1);
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED";
    }
}


void matrix_wrong_creating_test() {
    try {
        Matrix a(0, 0);
        std::cout << "FAILED\n";
    } catch (const std::string &s) {
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void matrix_copy_creating_test() {
    try {
        Matrix a(10, 10);
        Matrix b(a);
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void get_shape_test() {
    try {
        Matrix a(10, 20);
        Matrix b(a);
        auto size1 = a.get_shape();
        auto size2 = b.get_shape();
        std::pair<size_t, size_t> size = {10, 20};
        if (size1 != size || size2 != size) {
            throw "Get_shape error";
        }
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void get_rows_test() {
    try {
        Matrix a(10, 20);
        Matrix b(a);
        size_t size1 = a.get_rows();
        size_t size2 = b.get_rows();
        if (size1 != size2) {
            throw "Get_rows error";
        }
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void get_cols_test() {
    try {
        Matrix a(10, 20);
        Matrix b(a);
        size_t size1 = a.get_columns();
        size_t size2 = b.get_columns();
        if (size1 != size2) {
            throw "Get_cols error";
        }
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void double_brackets_test() {
    try {
        size_t r = 10, c = 20;
        Matrix a(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                a[i][j] = i * c + j;
            }
        }
        a[0][1] = 1;
        a[0][0] = a[0][1];
        if (a[0][0] != 1) {
            throw "Matrix modification failed";
        }
        int t = a[0][0];
        if (t != 1) {
            throw "Matrix reading failed";
        }
        a[0][0] = a[0][0] + t + 10;
        if (a[0][0] != 12) {
            throw "Matrix reading and modification failed";
        }
        a[0][0] = (a[0][0] = t + a[0][0]);
        if (a[0][0] != 13) {
            throw "Matrix reading, modification and return failed";
        }
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void matrix_equal_test() {
    try {
        size_t rows = 10, cols = 20;
        Matrix a(rows, cols);
        Matrix b(a);
        Matrix c(a);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                a[i][j] = i * cols + j;
                b[i][j] = a[i][j];
                c[i][j] = j;
            }
        }
        if (!(a == b)) {
            throw "Equal operator error";
        }
        if (a == c) {
            throw "Equal operator error";
        }
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void matrix_not_equal_test() {
    try {
        size_t rows = 10, cols = 20;
        Matrix a(rows, cols);
        Matrix b(a);
        Matrix c(a);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                a[i][j] = i * cols + j;
                b[i][j] = a[i][j];
                c[i][j] = j;
            }
        }
        if (a != b) {
            throw "Equal operator error: a != b";
        }
        if (!(a != c)) {
            throw "Equal operator error: !(a != c)";
        }
        std::cout << "OK\n";
    } catch (const char *s) {
        std::cout << "FAILED: " << s << "\n";
    }
    catch (...) {
        std::cout << "FAILED\n";
    }
}


void matrix_scalar_mul_test() {
    try {
        size_t rows = 10, cols = 20;
        Matrix a(rows, cols);
        Matrix c(a);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                a[i][j] = i * cols + j;
                c[i][j] = a[i][j] * 3;
            }
        }
        a *= 3;
        if (a != c) {
            throw "Equal operator error";
        }
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void matrix_addition_test() {
    try {
        size_t rows = 10, cols = 20;
        Matrix a(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                a[i][j] = i * cols + j;
            }
        }
        Matrix b(a);
        Matrix c = a + b;
        Matrix d(a);
        d *= 2;
        if (c != d) {
            throw "Matrix addition error";
        }
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void matrix_output_test() {
    try {
        std::ofstream fout("output_test.txt");

        size_t rows = 10, cols = 20;
        Matrix a(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                a[i][j] = i * cols + j;
            }
        }
        fout << a;
        fout.close();

        std::ifstream fin("output_test.txt");

        Matrix b(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int t;
                fin >> t;
                b[i][j] = t;
            }
        }
        fin.close();

        if (a != b) {
            throw "Output error";
        }

        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void default_lib_using_test() {
    try {
        const size_t rows = 5;
        const size_t cols = 3;

        Matrix m(rows, cols);

        if (m.get_rows() != 5) {
            throw "error";
        }
        if (m.get_columns() != 3) {
            throw "error";
        }

        m[1][2] = 5;
        double x = m[4][1];
        ++x;
        m *= 3;

        Matrix m1(rows, cols);

        if (m1 == m) {
            m1[0][0] = 0;
        }
        Matrix m2 = m1 + m;
        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


int main() {
    matrix_default_creating_test();
    matrix_wrong_creating_test();
    matrix_copy_creating_test();
    get_shape_test();
    get_rows_test();
    get_cols_test();
    double_brackets_test();
    matrix_equal_test();
    matrix_not_equal_test();
    matrix_scalar_mul_test();
    matrix_addition_test();
    matrix_output_test();
    default_lib_using_test();
}