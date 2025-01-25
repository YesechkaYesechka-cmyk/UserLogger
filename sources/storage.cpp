#include "storage.h"

Storage::UserAndItsSessions::UserAndItsSessions(
        const User &user,
        const Storage::UserAndItsSessions::session_set_t &sessions)
    : m_user(user), m_sessions(sessions)
{}

bool Storage::InsertUser(const User &user) {
    std::pair<std::map<Storage::storage_key_t, Storage::storage_value_t>::iterator, bool> pair =
            m_storage.insert({user.m_username, {user, {}}});
    return pair.second;
}

// TODO: InsertSession()

bool Storage::InsertSession(const std::string &username, const LogSession &session) {
    auto it = m_storage.find(username);
    if (it == m_storage.end()) {
        return false;
    }
    auto &userSessions = it->second.GetSessions();
    auto result = userSessions.insert(session);
    return result.second;
}



