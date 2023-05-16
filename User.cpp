#include "User.h"

User::User(int id, bool isVip)  : m_id(id), m_isVip(isVip), m_currentGroup(nullptr),
                                  m_rootOfUserGroup(0, nullptr){
    for(int i = 0; i < GENRE_AMOUNT; i++)
    {
        m_viewsByGenre[i] = 0;
        m_viewOfGroupBeforeJoining[i] = 0;
    }
}

int User::getId() const {
    return m_id;
}

bool User::isVip() const {
    return m_isVip;
}

int User::getViewsByGenre(Genre genre) const {
    return m_viewsByGenre[static_cast<int>(genre)];
}

Group* User::getUserGroup() const{
    return m_currentGroup;
}

AVL_node<int, User*> User::getRootOfUserGroup() const {
    return m_rootOfUserGroup;
}

void User::addViewsByGenre(Genre genre,int views) {
    m_viewsByGenre[static_cast<int>(genre)] = views;
}

int User::getViewOfGroupBeforeJoining(Genre genre) const {
    return m_viewOfGroupBeforeJoining[static_cast<int>(genre)];
}

void User::setViewOfGroupBeforeJoining(Genre genre, int views) {
    m_viewOfGroupBeforeJoining[static_cast<int>(genre)] = views;
}

void User::setUserGroup(Group* group){
    m_currentGroup = group;
}

void User::setRootOfUserGroup(AVL_node<int, User*> const &user) {
    m_rootOfUserGroup = user;
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