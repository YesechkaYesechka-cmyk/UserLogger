#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

struct GECOS {
    std::string m_fullname;
    std::string m_address;
    std::string m_workmobile;
    std::string m_homemobile;

    GECOS() = default;
    GECOS(const std::string &gecos_str);
};

//#define BUILD_GOOGLE_TEST

class User {

#ifdef BUILD_GOOGLE_TEST
public:
#else
private:
#endif
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

//public:
//    std::string get_username()const;
//    unsigned short get_uid()const;
//    unsigned short get_gid()const;
//    GECOS get_gecos()const;
//    std::string get_homedir_path()const;
//    std::string get_homedir_path()const;
};

