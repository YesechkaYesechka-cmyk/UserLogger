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
    GECOS(const std::string &gecos_str);
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
    User()=default;
    User(const std::string &str);
    friend std::istream &operator>>(std::istream &in, User &user);
};