#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>

int IsCorrectMinutes(const std::string& str);

std::string TrimLeadingSpaces(const std::string &str);

std::string SkipFirstWord(const std::string &str);

void ParseDateString(const std::string &str, std::string &month, unsigned short &day, unsigned short &hour,
                     unsigned short &minutes);



void ValidateTimeFormat(const std::string &str);

struct Date{
    std::string m_month;
    unsigned short m_day;
    unsigned short m_hour;
    unsigned short m_minutes;
    struct Duration{
        unsigned short m_day;
        unsigned short m_hour;
        unsigned short m_minutes;
        Duration(const std::string &str);
        Duration()=default;
    private:
        void ValidateDurationString(const std::string &str);
        void ParseDurationString(const std::string &str);

    } m_duration;
    Date(const std::string &str, const Duration& duration = Duration{});
    Date()=default;
};

std::ostream &operator<<(std::ostream &out, const Date &date);
std::ostream &operator<<(std::ostream &out, const Date::Duration &duration);
bool operator<(const Date& l, const Date& r);

class LogSession{
#ifdef BUILD_GOOGLE_TEST
public:
#else
private:
#endif
    std::string m_username;
    std::string m_tty_name;
    std::string m_hostname;
    Date m_date;

public:
    LogSession(const std::string &str);
    LogSession()=default;
    friend std::istream &operator>>(std::istream &in, LogSession &log_session);
    friend std::ostream &operator<<(std::ostream &out, const LogSession &log_session);
private:
    void ParseUsername(std::stringstream &ss);
    void ParseTTYName(std::stringstream &ss);
    std::string ParseHostnameAndGetDateTime(std::stringstream &ss);
    std::string ExtractDuration(std::string &date_time_str);
};