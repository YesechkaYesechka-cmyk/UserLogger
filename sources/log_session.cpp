#include "log_session.h"
#include <sstream>


Date::Date(const std::string &str) {
    std::string custom_str{str};
    int i = 0;
    while (std::isspace(custom_str[i])) i++;
    custom_str = custom_str.substr(i, custom_str.size() - i);
    size_t idx_spase = custom_str.find_first_of(" \t");
    // todo: удалить первые символы или взять подстроку от первого пробела
    custom_str = custom_str.substr(idx_spase + 1);
    char mon_str[64];
    int ret = sscanf(custom_str.data(), "%s %hu %hu:%hu", mon_str, &m_day, &m_hour, &m_minutes);
    if (ret == 4) {
        m_month = std::string(mon_str);
        size_t time_pos = custom_str.find(':');
        if (time_pos != (std::string::npos && time_pos >= 3) ){
            std::string time_str = custom_str.substr(time_pos - 2, 5);
            if (time_str.size() == 5 && time_str[2] == ':' && std::isdigit(time_str[0]) &&
                std::isdigit(time_str[1]) && std::isdigit(time_str[3]) && std::isdigit(time_str[4])) {
                sscanf(time_str.c_str(), "%hu:%hu", &m_hour, &m_minutes);
            } else throw std::exception();
        }
    } else throw std::exception();
}

Date::Duration::Duration(const std::string &str)
        : m_day{}, m_hour{}, m_minutes{} {
    if (str.find_first_not_of("+:0123456789") != std::string::npos || !std::isdigit(str[0]) ||
        !std::isdigit(str.back()))
        throw std::exception();
    int ret = 0;
    char minutes_str[64];
    ret = sscanf(str.data(), "%hd+%hd:%s", &m_day, &m_hour, minutes_str);
    if (ret != 3) {
        ret = sscanf(str.data(), "%hd:%hd", &m_hour, &m_minutes);
        if (ret != 2)
            throw std::exception();
    } else {  // если минуты присутствуют в записи Duration
        int minutes = IsCorrectMinutes(minutes_str);
        if (minutes == -1) throw std::exception();
        m_minutes = minutes;
    }
}

int IsCorrectMinutes(const std::string &str) {
    if (str.size() != 2) return -1;
    int minutes = std::stoi(str);
    if (minutes >= 0 && minutes <= 59) return minutes;
    else return -1;
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