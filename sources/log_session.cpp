#include <sstream>
#include "log_session.h"
#include "utils.h"

/*
 * note: Поле duration
 */

std::string TrimLeadingSpaces(const std::string &str) {
    size_t i = 0;
    while (i < str.size() && std::isspace(str[i])) {
        i++;
    }
    return str.substr(i);
}

// Пропускает первое слово (например, день недели) и возвращает оставшуюся часть строки
std::string SkipFirstWord(const std::string &str) {
    size_t idx_space = str.find_first_of(" \t");
    if (idx_space == std::string::npos) {
        throw std::invalid_argument("Invalid input string: missing space after first word");
    }
    return str.substr(idx_space + 1);
}

// Парсит оставшуюся строку, извлекая месяц, день, часы и минуты
void ParseDateString(const std::string &str, std::string &month, unsigned short &day, unsigned short &hour, unsigned short &minutes) {
    char mon_str[64];
    int ret = sscanf(str.data(), "%s %hu %hu:%hu", mon_str, &day, &hour, &minutes);
    if (ret == 4) {
        month = std::string(mon_str);
        ValidateTimeFormat(str);
    } else {
        throw std::invalid_argument("Invalid date format: " + str);
    }
}

// Проверяет правильность формата времени
void ValidateTimeFormat(const std::string &str) {
    size_t time_pos = str.find(':');
    if (time_pos != std::string::npos && time_pos >= 3) {
        std::string time_str = str.substr(time_pos - 2, 5);
        if (!(time_str.size() == 5 && time_str[2] == ':' &&
              std::isdigit(time_str[0]) && std::isdigit(time_str[1]) &&
              std::isdigit(time_str[3]) && std::isdigit(time_str[4]))) {
            throw std::invalid_argument("Invalid time format: " + str);
        }
    } else {
        throw std::invalid_argument("Invalid time format: " + str);
    }
}

// Конструктор
Date::Date(const std::string &str, const Duration &duration)
        : m_duration{duration} {
    std::string custom_str = TrimLeadingSpaces(str);
    custom_str = SkipFirstWord(custom_str);
    ParseDateString(custom_str, m_month, m_day, m_hour, m_minutes);
}



void Date::Duration::ValidateDurationString(const std::string &str) {
    if (str.find_first_not_of("+:0123456789") != std::string::npos ||
        !std::isdigit(str[0]) || !std::isdigit(str.back())) {
        throw std::exception();
    }
}

void Date::Duration::ParseDurationString(const std::string &str) {
    int ret = 0;
    char minutes_str[64];

    ret = sscanf(str.data(), "%hd+%hd:%s", &m_day, &m_hour, minutes_str);
    if (ret == 3) {
        int minutes = IsCorrectMinutes(minutes_str);
        if (minutes == -1) {
            throw std::exception();
        }
        m_minutes = minutes;
    } else {
        ret = sscanf(str.data(), "%hd:%hd", &m_hour, &m_minutes);
        if (ret != 2) {
            throw std::exception();
        }
    }
}

Date::Duration::Duration(const std::string &str)
        : m_day{}, m_hour{}, m_minutes{} {
    ValidateDurationString(str);
    ParseDurationString(str);
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

    ParseUsername(ss);
    ParseTTYName(ss);

    std::string date_time_str = ParseHostnameAndGetDateTime(ss);

    std::string duration_str = ExtractDuration(date_time_str);

    m_date = Date(date_time_str);
    if (!duration_str.empty()) {
        m_date.m_duration = Date::Duration(duration_str);
    }
}

void LogSession::ParseUsername(std::stringstream &ss) {
    ss >> m_username;
}

void LogSession::ParseTTYName(std::stringstream &ss) {
    if (m_username == "reboot") {
        ss >> m_tty_name;
        m_tty_name += " ";
        std::string tmp;
        ss >> tmp;
        m_tty_name += tmp;
    } else {
        ss >> m_tty_name;
    }
}

std::string LogSession::ParseHostnameAndGetDateTime(std::stringstream &ss) {
    std::string word;
    while (ss >> word) {
        if (std::isupper(word[0])) {
            break;         }
        if (!m_hostname.empty()) {
            m_hostname += " ";
        }
        m_hostname += word;
    }

    std::string date_time_str = word;
    std::getline(ss, word);
    date_time_str += word;
    date_time_str = TrimLeadingSpaces(date_time_str);

    return date_time_str;
}

std::string LogSession::ExtractDuration(std::string &date_time_str) {
    size_t duration_start = date_time_str.find_last_of('(');
    std::string duration_str;

    if (duration_start != std::string::npos) {
        size_t duration_end = date_time_str.find(')', duration_start);
        if (duration_end != std::string::npos) {
            duration_str = date_time_str.substr(duration_start + 1, duration_end - duration_start - 1);
        }

        date_time_str = date_time_str.substr(0, duration_start - 1);
    }
    return duration_str;
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

bool operator<(const Date &l, const Date &r) {
    //TODO (yaroslava): implementation
    if (GetMonthInteger(l.m_month) != GetMonthInteger(r.m_month)) {
        return GetMonthInteger(l.m_month) < GetMonthInteger(r.m_month);
    }

    if (l.m_day != r.m_day) {
        return l.m_day < r.m_day;
    }
    if (l.m_hour != r.m_hour) {
        return l.m_hour < r.m_hour;
    }
    if (l.m_minutes != r.m_minutes) {
        return l.m_minutes < r.m_minutes;
    }
    return false;
}