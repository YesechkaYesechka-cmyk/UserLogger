#include "storage.h"

Storage::UserAndItsSessions::UserAndItsSessions(const User &user,
                                                const Storage::UserAndItsSessions::session_set_t &sessions)
    : m_user(user), m_sessions(sessions)
{}


