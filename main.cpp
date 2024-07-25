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
const char* filepath = "D:\\UserLogger\\files\\passwd.txt";
#elif linux
const char* filepath = "/home/user/dir/programming/C++/UserLogger/files/passwd.txt";
#endif

#include "user.h"
int main(){
    User user;
    std::ifstream ifile{filepath};
    if(!ifile.is_open()) {
        std::cout<<"Error!!!";
        return -1;
    }
    while (!ifile.eof()) {
        ifile >> user;
    }



    return 0;
}

