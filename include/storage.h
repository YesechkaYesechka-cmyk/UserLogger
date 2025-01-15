#ifndef USERLOGGER_STORAGE_H
#define USERLOGGER_STORAGE_H

#include <string>
#include <map>
#include <set>

#include "log_session.h"
#include "user.h"

static auto comp = [](const LogSession& l, const LogSession& r) {
    return l.m_date < r.m_date;
};

class Storage {
public:

    class UserAndItsSessions {
    public:
        using session_comp = decltype(comp);
        using session_set_t = std::set<LogSession, session_comp>;

        UserAndItsSessions() = default;

        UserAndItsSessions(const User &user, const session_set_t &sessions);

        UserAndItsSessions(const UserAndItsSessions &other) = default;

        UserAndItsSessions &operator=(const UserAndItsSessions &other) = default;

        User GetUser() const { return m_user; };

        session_set_t GetSessions() const { return m_sessions; };

    private:
        User m_user;
        session_set_t m_sessions;
    };


    using storage_key_t = std::string;
    using storage_value_t = UserAndItsSessions;
private:

    std::map<storage_key_t, storage_value_t> m_storage;

};


#endif //USERLOGGER_STORAGE_H
