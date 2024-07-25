#include "user.h"
#include <sstream>
#include <algorithm>

/*
 * Считывает одну строку из файла и раскладывает ее содержимое по полям класса User
 * Пример строки конфигурационного файла:
 * root:x:0:0:root,administrator,outsourcer:/root:zsh
 */
std::istream &operator>>(std::istream &in, User &user) {
    std::string Line;
    std::getline(in, Line);
    if (!Line.empty()) {
        size_t begin = 0;
        size_t pos = 0;

        // == username ==
        pos = Line.find(':', begin);
        user.m_username = Line.substr(begin, pos);
        begin = pos + 3;

        // == uid ==
        pos = Line.find(':', begin);
        user.m_uid = stoi(Line.substr(begin, pos - begin), nullptr, 10);
        begin = ++pos;

        // == gid ==
        pos = Line.find(':', begin);
        user.m_gid = stoi(Line.substr(begin, pos-begin), nullptr, 10);
        begin = ++pos;

        // == GECOS ==
        pos = Line.find(':', begin);
        std::string gecos_str = Line.substr(begin, pos - begin);
        user.m_gecos = GECOS(gecos_str);
        begin = ++pos;

        // == homedir_path ==
        pos = Line.find(':', begin);
        user.m_homedir_path = Line.substr(begin, pos - begin);
        begin = ++pos;

        // == interpretator ==
        pos = Line.find(':', begin);
        user.m_interpretator = Line.substr(begin, pos - begin);
    }
    return in;
}

/*
2. Альтернатива sscanf()
3. Как считать m_gecos при sscanf и альтернативах
4. Зарегистрироваться на ГИТ
5. Поставить rustdesk
 */