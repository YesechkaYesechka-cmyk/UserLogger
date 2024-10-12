#include "log_session.h"
#include <sstream>


Date::Date(const std::string &str) {

}

Date::Duration::Duration(const std::string &str)
:m_day{}, m_hour{}, m_minutes{}
{
    if(str.find_first_not_of("+:0123456789") != std::string::npos || !std::isdigit(str[0]) || !std::isdigit(str.back())) throw std::exception();
    int ret = 0;
    ret = sscanf(str.data(), "%hd+%hd:%hd", &m_day, &m_hour, &m_minutes);
    if (ret != 3) {
        ret = sscanf(str.data(), "%hd:%hd", &m_hour, &m_minutes);
        if (ret != 2)
            throw std::exception();
    }

//    auto begin = str.begin();
//    if (auto pos = find(begin, str.end(), '+'); pos != str.end()) {
//        std::string day{str.begin(), pos};
//        m_day = std::strtol(day.data(), nullptr, 10);
//        begin = ++pos;
//    }
////    std::string hour{begin,begin+2};
////    m_hour = std::strtol(hour.data(), nullptr, 10);
////    std::string minute{begin+3,begin+5};
////    m_minutes = std::strtol(minute.data(), nullptr, 10);
//
//    std::string h_m{begin, str.end()};
//    sscanf(h_m.data(), "%hd:%hd", &m_hour, &m_minutes);
}

LogSession::LogSession(const std::string &str)
        : m_username(), m_tty_name(), m_hostname(), m_date_params() {
    std::stringstream ss(str);
    ss >> m_username;
    if (m_username == "reboot") {
        ss >> m_tty_name;
        m_tty_name += " ";
        std::string tmp;
        ss >> tmp;
        m_tty_name += tmp;
        // ...
    }
    ss >> m_tty_name;
    ss >> m_hostname;

}