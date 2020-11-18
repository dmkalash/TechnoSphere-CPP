#pragma once

#include <exception>
#include <sstream>


namespace Format {

    class KeyError : public std::exception {
        std::string m_error;
    public:
        KeyError();
        KeyError(const std::string &error);
        const char *what() const noexcept override;
    };


    class IndexError : public std::exception {
        std::string m_error;
    public:
        IndexError();
        IndexError(const std::string &error);
        const char *what() const noexcept override;
    };


    class ValueError : public std::exception {
        std::string m_error;
    public:
        ValueError();
        ValueError(const std::string &error);
        const char *what() const noexcept override;
    };


    template<class T>
    std::string template_to_string(const T &arg);

    std::string format(const std::string &s);

    template<class T, class... ArgsT>
    std::string format(const std::string &s, const T &arg, const ArgsT &... args);

    template<class T, class... ArgsT>
    std::string hformat_(const std::string &s, std::vector<std::string> &params, const T &arg, const ArgsT &... args);

    std::string hformat_(const std::string &s, const std::vector<std::string> &params);

    size_t get_key_(const std::string &s, int &i);
}

#include "format.tpp"
