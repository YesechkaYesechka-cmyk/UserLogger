/*
 Получить из форматированного текстового файла информацию о пользователях, авторизовавшихся в системе за последнее время.
 Создать хранилище информации об этих пользователях:
 1. сведения о самом пользователе (имя, uid, guid, интерпретатор, доп.информация, ...)
 2. сведения о сессии, в рамках которой этот пользователь был авторизован

 Сделать пользовательский интерфейс, который позволит обращаться к этому хранилищу и получать оттуда информацию по запросу:
 1. Кто
 2. Когда
 3. Как часто
 4. Способ авторизации
 5. Время авторизации
 */

#ifdef WIN64
const char *passwd_file_path = "D:\\UserLogger\\files\\passwd.txt";
const char *lastlog_file_path = "D:\\UserLogger\\files\\last.log";
#elif linux
const char* passwd_file_path = "/home/user/dir/programming/C++/UserLogger/files/passwd.txt";
const char *lastlog_file_path = "/home/user/dir/programming/C++/UserLogger/files/last.log";
#endif

#include "user.h"
#include "log_session.h"

#include <exception>

int main() {
    User user;
    std::ifstream ifile_passwd{passwd_file_path};
    if (!ifile_passwd.is_open()) {
        std::cout << "Error!!!";
        return -1;
    }
    while (!ifile_passwd.eof()) {
        ifile_passwd >> user;
        std::cout << user;
    }

    LogSession log_session;
    std::ifstream ifile_lastlog{lastlog_file_path};
    if (!ifile_lastlog.is_open()) {
        std::cout << "Error!!!";
        return -1;
    }
    while (!ifile_lastlog.eof()) {
        ifile_lastlog >> log_session;
        std::cout << log_session;
    }

    return 0;
}

