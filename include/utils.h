#ifndef USERLOGGER_UTILS_H
#define USERLOGGER_UTILS_H

#include <string>
#include <sstream>
#include <stdexcept>

enum class Months: int {
    JAN = 1,
    FEB=2,
    MAR=3,
    APR=4,
    MAY=5,
    JUN=6,
    JUL=7,
    AUG=8,
    SEP=9,
    OCT=10,
    NOV=11,
    DEC=12
};

Months GetMonthInteger(const std::string& month);
#endif //USERLOGGER_UTILS_H
