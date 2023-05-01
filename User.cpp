#include "User.h"

User::User(int id, bool isVip)  : m_id(id), m_isVip(isVip), m_viewsByGenre(new int [GENRE_AMOUNT]),
                                  m_viewOfGroupBeforeJoining(new int[GENRE_AMOUNT]){}