#include <iostream>
#include "serializer.hpp"
#include <string>
#include <sstream>


/////////////////////////// Structures


struct Data1
{
    uint64_t a;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a);
    }
};


struct Data2
{
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(b);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(b);
    }
};


struct Data3
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};


struct Data4
{
    uint64_t a;
    uint64_t b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};


struct Data5
{
    bool a;
    bool b;
    bool c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};


struct Data6
{
    bool a;
    uint64_t b;
    int c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};



bool check(std::stringstream &out, const std::string &s)
{
    std::string t;
    out >> t;
    return t == s;
}


/////////////////////////// Serializer


void ser_creating_string_test()
{
    try {
        std::stringstream stream;
        Serializer ser(stream);
        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void ser_creating_ofstream_test()
{
    try {
        Serializer ser(std::cout);
        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void ser_u_single_save_string_test()
{
    try {
        Data1 x { 1 };

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        if (er != Error::NoError || !check(stream, "1")) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void ser_b_single_save_string_test()
{
    try {
        Data2 x { false };

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        if (er != Error::NoError || !check(stream, "false")) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void ser_mult_save_string_test()
{
    try {
        Data3 x {0, true, 200};

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        if (er != Error::NoError || !check(stream, "0") || !check(stream, "true") || !check(stream, "200")) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void ser_u_mult_save_string_test()
{
    try {
        Data4 x {100, 0, 2020};

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        if (er != Error::NoError || !check(stream, "100") || !check(stream, "0") || !check(stream, "2020")) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void ser_b_mult_save_string_test()
{
    try {
        Data5 x {true, true, false};

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        if (er != Error::NoError || !check(stream, "true") || !check(stream, "true") || !check(stream, "false")) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void ser_bad_type_save_string_test()
{
    try {
        Data6 x {true, 10, -100};

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        std::cout << "FAILED\n";
    } catch (std::bad_typeid &e) {
        std::cout << "OK: unexpected type\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


/////////////////////////// Deserializer


void deser_creating_string_test()
{
    try {
        std::stringstream stream;
        Deserializer deser(stream);
        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void deser_creating_ofstream_test()
{
    try {
        Deserializer deser(std::cin);
        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void deser_u_single_save_string_test()
{
    try {
        Data1 x { 1 };

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);
        x.a = 2;

        Deserializer deser(stream);
        er = deser.load(x);

        if (er != Error::NoError || x.a != 1) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void deser_b_single_save_string_test()
{
    try {
        Data2 x { false }, y {true};

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        Deserializer deser(stream);
        er = deser.load(y);

        if (er != Error::NoError || y.b) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void deser_mult_save_string_test()
{
    try {
        Data3 x {0, true, 200}, y {100, false, 0};

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        Deserializer deser(stream);
        er = deser.load(y);

        if (er != Error::NoError || y.a != 0 || !y.b || y.c != 200) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void deser_u_mult_save_string_test()
{
    try {
        Data4 x {100, 0, 2020}, y;

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        Deserializer deser(stream);
        er = deser.load(y);

        if (er != Error::NoError || y.a != 100 || y.b != 0 || y.c != 2020) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void deser_b_mult_save_string_test()
{
    try {
        Data5 x {true, true, false};

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        Deserializer deser(stream);
        er = deser.load(x);

        if (er != Error::NoError || !x.a || !x.b || x.c) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch(...) {
        std::cout << "FAILED\n";
    }
}


void deser_bad_type_save_string_test()
{
    try {
        Data6 x {true, 10, 100};
        Data5 y;

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        Deserializer deser(stream);
        er = deser.load(y);

        std::cout << "FAILED\n";
    } catch (std::bad_typeid &e) {
        std::cout << "OK: unexpected type\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void deser_b_bad_stream_save_string_test()
{
    try {
        Data4 x {20, 10, 100};
        Data5 y;

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(x);

        Deserializer deser(stream);
        er = deser.load(y);

        if (er != Error::CorruptedArchive) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void deser_u_bad_stream_save_string_test()
{
    try {
        Data4 x {1, 2, 3};
        Data5 y;

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(y);

        Deserializer deser(stream);
        er = deser.load(x);

        if (er != Error::CorruptedArchive) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void deser_few_bad_stream_save_string_test()
{
    try {
        Data3 x {1, 1, 1};
        Data2 y;

        std::stringstream stream;
        Serializer serializer(stream);
        Error er = serializer.save(y);

        Deserializer deser(stream);
        er = deser.load(x);

        if (er != Error::CorruptedArchive) {
            throw -1;
        }

        Data3 x2 {1, 1, 1};
        Data1 y2;

        std::stringstream stream2;
        Serializer serializer2(stream2);
        er = serializer2.save(x2);

        Deserializer deser2(stream2);
        er = deser2.load(y2);

        if (er != Error::NoError || !y2.a) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


void deser_bad_stream_test()
{
    try {
        std::stringstream stream;
        stream << "^   ";

        Deserializer deser(stream);

        Data1 x;
        Error er = deser.load(x);

        if (er != Error::CorruptedArchive) {
            throw -1;
        }

        std::stringstream stream1;
        stream1 << " -005 ";
        Deserializer deser1(stream1);

        er = deser1.load(x);

        if (er != Error::CorruptedArchive) {
            throw -1;
        }

        std::stringstream stream2;
        stream2 << " -00 ";
        Deserializer deser2(stream2);

        er = deser2.load(x);

        if (er == Error::CorruptedArchive || x.a != 0) {
            throw -1;
        }

        std::stringstream stream3;
        stream3 << " 99999999999999999999999999999999999999999999999 ";
        Deserializer deser3(stream3);

        er = deser3.load(x);

        if (er != Error::CorruptedArchive) {
            throw -1;
        }

        std::cout << "OK\n";
    } catch (...) {
        std::cout << "FAILED\n";
    }
}


int main()
{
    ser_creating_string_test();
    ser_creating_ofstream_test();
    ser_u_single_save_string_test();
    ser_b_single_save_string_test();
    ser_mult_save_string_test();
    ser_u_mult_save_string_test();
    ser_b_mult_save_string_test();
    ser_bad_type_save_string_test();

    deser_creating_string_test();
    deser_creating_ofstream_test();
    deser_u_single_save_string_test();
    deser_b_single_save_string_test();
    deser_mult_save_string_test();
    deser_u_mult_save_string_test();
    deser_b_mult_save_string_test();
    deser_bad_type_save_string_test();

    deser_b_bad_stream_save_string_test();
    deser_u_bad_stream_save_string_test();
    deser_few_bad_stream_save_string_test();
    deser_bad_stream_test();
    return 0;
}
