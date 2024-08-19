#include "user.h"
#include <sstream>
#include <algorithm>

/*
 * Считывает одну строку из файла и раскладывает ее содержимое по полям класса User
 * Пример строки конфигурационного файла:
 * root:x:0:0:root,administrator,outsourcer:/root:zsh
 */

User::User(const std::string &str){
    if (!str.empty()) {
        size_t begin = 0;
        size_t pos = 0;

        // == username ==
        pos = str.find(':', begin);
        this->m_username = str.substr(begin, pos);
        begin = pos + 3;

        // == uid ==
        pos = str.find(':', begin);
        this->m_uid = stoi(str.substr(begin, pos - begin), nullptr, 10);
        begin = ++pos;

        // == gid ==
        pos = str.find(':', begin);
        this->m_gid = stoi(str.substr(begin, pos-begin), nullptr, 10);
        begin = ++pos;

        // == GECOS ==
        pos = str.find(':', begin);
        std::string gecos_str = str.substr(begin, pos - begin);
        this->m_gecos = GECOS(gecos_str);
        begin = ++pos;

        // == homedir_path ==
        pos = str.find(':', begin);
        this->m_homedir_path = str.substr(begin, pos - begin);
        begin = ++pos;

        // == interpretator ==
        pos = str.find(':', begin);
        this->m_interpretator = str.substr(begin, pos - begin);
    }
}

std::istream &operator>>(std::istream &in, User &user) {
    std::string Line;
    std::getline(in, Line);
    user = User(Line);
    return in;
}

GECOS::GECOS(const std::string &gecos_str)
        : m_fullname(), m_address(), m_workmobile(), m_homemobile()
{
    size_t begin = 0;
    size_t pos = 0;
    pos = std::count(gecos_str.begin(), gecos_str.end(), ',');
    if (pos != 3) {
        m_fullname = gecos_str;
    } else {
        //=========m_fullname==========
        pos = gecos_str.find(',', begin);
        m_fullname = gecos_str.substr(begin, pos - begin);
        begin = pos + 1;

        //=========m_address==========
        pos = gecos_str.find(',', begin);
        m_address = gecos_str.substr(begin, pos - begin);
        begin = pos + 1;

        //=========m_workmobile==========
        pos = gecos_str.find(',', begin);
        m_address = gecos_str.substr(begin, pos - begin);
        begin = pos + 1;

        //=========m_homemobile==========
        pos = gecos_str.find(',', begin);
        m_homemobile = gecos_str.substr(begin, pos - begin);
    }
}

/*
2. Альтернатива sscanf()
3. Как считать m_gecos при sscanf и альтернативах
4. Зарегистрироваться на ГИТ
5. Поставить rustdesk
 */