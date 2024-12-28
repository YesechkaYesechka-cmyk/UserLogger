#include "log_session.h"
#include <sstream>

/*
 * note: Поле duration
 */
Date::Date(const std::string &str, const Duration &duration)
        : m_duration{duration} {
    std::string custom_str{str};
    int i = 0;
    while (std::isspace(custom_str[i])) i++;
    custom_str = custom_str.substr(i, custom_str.size() - i);
    size_t idx_spase = custom_str.find_first_of(" \t");
    custom_str = custom_str.substr(idx_spase + 1);
    char mon_str[64];
    int ret = sscanf(custom_str.data(), "%s %hu %hu:%hu", mon_str, &m_day, &m_hour, &m_minutes);
    if (ret == 4) {
        m_month = std::string(mon_str);
        size_t time_pos = custom_str.find(':');
        if (time_pos != (std::string::npos && time_pos >= 3)) {
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
        : m_username(), m_tty_name(), m_hostname(), m_date() {
    std::stringstream ss(str);
    ss >> m_username;

    if (m_username == "reboot") {
        ss >> m_tty_name;
        m_tty_name += " ";
        std::string tmp;
        ss >> tmp;
        m_tty_name += tmp;
    } else { ss >> m_tty_name; }

    std::string word;
    while (ss >> word) {
        if (std::isupper(word[0])) {
            break;
        }
        if (!m_hostname.empty()) {
            m_hostname += " ";
        }
        m_hostname += word;
    }


    std::string date_time_str = word;
    std::getline(ss, word);
    date_time_str += word;


    size_t first_non_space = date_time_str.find_first_not_of(" \t");
    if (first_non_space != std::string::npos) {
        date_time_str = date_time_str.substr(first_non_space);
    }


    size_t duration_start = date_time_str.find_last_of('(');
    std::string duration_str;
    if (duration_start != std::string::npos) {
        duration_str = date_time_str.substr(duration_start + 1, date_time_str.find(')') - duration_start - 1);

        date_time_str = date_time_str.substr(0, duration_start - 1);
    }
    m_date = Date(date_time_str);
    if (!duration_str.empty()) {
        m_date.m_duration = Date::Duration(duration_str);
    }
}

std::istream &operator>>(std::istream &in, LogSession &log_session) {
    std::string Line;
    std::getline(in, Line);
    log_session = LogSession(Line);
    return in;
}

std::ostream &operator<<(std::ostream &out, const LogSession &log_session) {
    out << log_session.m_username << '\t' << log_session.m_tty_name << '\t' << log_session.m_hostname << '\t'
        << log_session.m_date << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const Date &date) {
    out << date.m_month << '\t' << date.m_day << '\t' << date.m_hour << '\t' << date.m_minutes << '\t'
        << date.m_duration;
    return out;
}

std::ostream &operator<<(std::ostream &out, const Date::Duration &duration) {
    out << duration.m_day << '\t' << duration.m_hour << '\t' << duration.m_minutes;
    return out;
}
