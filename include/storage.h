#ifndef USERLOGGER_STORAGE_H
#define USERLOGGER_STORAGE_H

#include <string>
#include <map>
#include <set>


#include "log_session.h"
#include "user.h"

struct Comparator {
    bool operator()(const LogSession &l, const LogSession &r) const {
        return l.m_date < r.m_date;
    };
};

class Storage {
public:
    Storage()=default;
    Storage(const Storage&)=delete;
    Storage& operator=(const Storage&)=delete;

    bool InsertUser(const User& user);
    bool InsertSession(const std::string &username, const LogSession &session);

    inline size_t Size() const {
        return m_storage.size();
    }

    class UserAndItsSessions {
    public:
        using session_comp = Comparator;
        using session_set_t = std::set<LogSession, session_comp>;
        UserAndItsSessions() = default;

        UserAndItsSessions(const User &user, const session_set_t &sessions);

        UserAndItsSessions(const UserAndItsSessions &other) = default;

        UserAndItsSessions &operator=(const UserAndItsSessions &other) = default;

        User GetUser() const { return m_user; };

        session_set_t GetSessions() const { return m_sessions; };

        session_set_t& GetSessions() { return m_sessions;};

#ifdef BUILD_GOOGLE_TEST
    public:
#else
    private:
#endif
        User m_user;
        session_set_t m_sessions;
    };

    using storage_key_t = std::string;
    using storage_value_t = UserAndItsSessions;

#ifdef BUILD_GOOGLE_TEST
public:
#else
    private:
#endif
    std::map<storage_key_t, storage_value_t> m_storage;
};


#endif //USERLOGGER_STORAGE_H
