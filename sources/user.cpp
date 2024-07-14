#include "user.h"

std::istream &operator>>(std::istream &in, User &user) {
    std::string Line;
    std::getline(in, Line);
    if (!Line.empty()) {
        sscanf(Line.data(), "%s:x:%d:%d:%s:%s:%s", user.m_username.data(),
               user.m_uid,
               user.m_gid,
               user.m_gecos,
               user.m_homedir_path.data(),
               user.m_interpretator.data());
    }

    return in;
}

/*
1. Почему .data()
2. Альтернатива sscanf()
3. Как считать m_gecos при sscanf и альтернативах
4. Зарегистрироваться на ГИТ
5. Поставить rustdesk
 */