#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>


struct GECOS {
    std::string m_fullname;
    std::string m_address;
    std::string m_workmobile;
    std::string m_homemobile;

    GECOS() = default;

    GECOS(const std::string &gecos_str)
    : m_fullname(), m_address(), m_workmobile(), m_homemobile()
    {
        size_t begin = 0;
        size_t pos = 0;
        pos = std::count(gecos_str.begin(), gecos_str.end(), ',');
        if (pos != 3) {
            m_fullname = gecos_str;
        } else {
            //=========m_fullname==========
            pos = gecos_str.find(',', begin);
            m_fullname = gecos_str.substr(begin, pos - begin);
            begin = pos + 1;

            //=========m_address==========
            pos = gecos_str.find(',', begin);
            m_address = gecos_str.substr(begin, pos - begin);
            begin = pos + 1;

            //=========m_workmobile==========
            pos = gecos_str.find(',', begin);
            m_address = gecos_str.substr(begin, pos - begin);
            begin = pos + 1;

            //=========m_homemobile==========
            pos = gecos_str.find(',', begin);
            m_homemobile = gecos_str.substr(begin, pos - begin);
        }
    }
};

class User {
private:
    std::string m_username;
    unsigned short m_uid;
    unsigned short m_gid;
    GECOS m_gecos;
    std::string m_homedir_path;
    std::string m_interpretator;
public:
    friend std::istream &operator>>(std::istream &in, User &user);
};