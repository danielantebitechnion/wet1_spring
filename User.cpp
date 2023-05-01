#include "User.h"

User::User(int id, bool isVip)  : m_id(id), m_isVip(isVip), m_viewsByGenre(new int [GENRE_AMOUNT]),
                                  m_viewOfGroupBeforeJoining(new int[GENRE_AMOUNT]){}

int User::getId() const {
    return m_id;
}

bool User::isVip() const {
    return m_isVip;
}

int User::getViewsByGenre(Genre genre) const {
    return m_viewsByGenre[static_cast<int>(genre)];
}

void User::setViewsByGenre(Genre genre,int views) {
    m_viewsByGenre[static_cast<int>(genre)] = views;
}

int User::getViewOfGroupBeforeJoining(Genre genre) const {
    return m_viewOfGroupBeforeJoining[static_cast<int>(genre)];
}

void User::setViewOfGroupBeforeJoining(Genre genre, int views) {
    m_viewOfGroupBeforeJoining[static_cast<int>(genre)] = views;
}

void User::print() const {
    std::cout << "User id: " << m_id << ", is VIP: " << m_isVip << std::endl;
    std::cout << "Views by genre: ";
    for (int i = 0; i < GENRE_AMOUNT; i++) {
        std::cout << m_viewsByGenre[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Views of group before joining: ";
    for (int i = 0; i < GENRE_AMOUNT; i++) {
        std::cout << m_viewOfGroupBeforeJoining[i] << " ";
    }
    std::cout << std::endl;
}