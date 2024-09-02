#include "log_session.h"
#include <sstream>


Date::Date(const std::string &str) {

}

Date::Duration::Duration(const std::string &str) {
    auto begin = str.begin();
    if (auto pos = find(begin, str.end(), '+'); pos != str.end()) {
        std::string day{str.begin(), pos};
        m_day = std::strtol(day.data(), nullptr, 10);
        begin = ++pos;
    }
    // begin в любом случае является точкой, где начинаются часы...


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