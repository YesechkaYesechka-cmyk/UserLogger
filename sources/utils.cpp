#include "utils.h"

Months GetMonthInteger(const std::string &month) {
    if (month == "Jan") return Months::JAN;
    else if (month == "Feb") return Months::FEB;
    else if (month == "Mar") return Months::MAR;
    else if (month == "Apr") return Months::APR;
    else if (month == "May") return Months::MAY;
    else if (month == "Jun") return Months::JUN;
    else if (month == "Jul") return Months::JUL;
    else if (month == "Aug") return Months::AUG;
    else if (month == "Sep") return Months::SEP;
    else if (month == "Oct") return Months::OCT;
    else if (month == "Nov") return Months::NOV;
    else if (month == "Dec") return Months::DEC;
    else {
        throw std::invalid_argument("Invalid month name: " + month);
    }
}
