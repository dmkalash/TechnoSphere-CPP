#pragma once
#include <iostream>


enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
    std::ostream &out_;
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out);

    template <class T>
    Error save(T& object);

    template <typename T, class... ArgsT>
    Error operator()(const T &arg, const ArgsT & ...args);

    template <typename T>
    Error operator()(const T &arg);

    Error operator()(bool arg);
    Error operator()(uint64_t arg);
};


class Deserializer
{
    std::istream &in_;
public:
    explicit Deserializer(std::istream& in);

    template <class T>
    Error load(T& object);

    template <typename T, class... ArgsT>
    Error operator()(T &arg, ArgsT & ...args);

    template <typename T>
    Error operator()(T &arg);

    Error operator()(bool &arg);
    Error operator()(uint64_t &arg);
};


#include "serializer.tpp"
