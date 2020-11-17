#include <string>
#include <vector>


namespace Format
{
    KeyError::KeyError() {}
    KeyError::KeyError(const std::string &error) : m_error(error) {}
    const char * KeyError::what() const noexcept
    {
        return m_error.c_str();
    }


    IndexError::IndexError() {}
    IndexError::IndexError(const std::string &error) : m_error(error) {}
    const char * IndexError::what() const noexcept
    {
        return m_error.c_str();
    }


    ValueError::ValueError() {}
    ValueError::ValueError(const std::string &error) : m_error(error) {}
    const char * ValueError::what() const noexcept
    {
        return m_error.c_str();
    }


    template<class T>
    std::string template_to_string(const T &arg) {
        std::stringstream st;
        st << arg;
        return st.str();
    }

    std::string format(const std::string &s)
    {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '}') {
                throw ValueError();
            } else if (s[i] == '{') {
                get_key_(s, i);
                throw IndexError();
            }
        }
        return s;
    }

    template<class T, class... ArgsT>
    std::string format(const std::string &s, T &&arg, ArgsT &&... args)
    {
        std::vector<std::string> params;
        return hformat_(s, params, std::forward<T>(arg), std::forward<ArgsT>(args)...);
    }


    template<class T, class... ArgsT>
    std::string hformat_(const std::string &s, std::vector<std::string> &params, T &&arg, ArgsT &&... args)
    {
        params.push_back(template_to_string(arg));
        return hformat_(s, params, std::forward<ArgsT>(args)...);
    }


    std::string hformat_(const std::string &s, const std::vector<std::string> &params)
    {
        std::string res;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '{') {
                size_t key = get_key_(s, i);
                if (key >= params.size()) {
                    throw IndexError();
                }
                res += params[key];
            } else if (s[i] == '}') {
                throw ValueError();
            } else {
                res += s[i];
            }
        }
        return res;
    }

    size_t get_key_(const std::string &s, int &i) {
        ++i;
        size_t key = 0;
        bool non_digit = false;
        while (i < s.size() && s[i] != '}') {
            if (!isdigit(s[i])) {
                ++i;
                non_digit = true;
                continue;
            }
            key = key * 10 + s[i] - '0';
            ++i;
        }
        if (i == s.size()) {
            throw ValueError();
        }
        if (non_digit) {
            throw KeyError();
        }

        return key;
    }
}
