#include "User.h"

User::User(int id, bool isVip)  : m_id(id), m_isVip(isVip), m_currentGroup(nullptr), m_isInGroup(false),m_viewsByGenre{},m_viewOfGroupBeforeJoining{}{
    for(int i=0;i<TOTAL_GENRES;i++){
        m_viewOfGroupBeforeJoining[i] = 0;
        m_viewsByGenre[i] = 0;
    }
}

int User::getId() const {
    return m_id;
}
bool User::isUserInGroup() const{
    return m_isInGroup;
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

void User::addViewsByGenre(Genre genre,int views) {
    m_viewsByGenre[static_cast<int>(genre)] += views;
}

int User::getViewOfGroupBeforeJoining(Genre genre) const {
    return m_viewOfGroupBeforeJoining[static_cast<int>(genre)];
}

void User::setViewOfGroupBeforeJoining(Genre genre, int views) {
    m_viewOfGroupBeforeJoining[static_cast<int>(genre)] = views;
}

void User::setUserGroup(Group* group){
    m_isInGroup = true;
    m_currentGroup = group;
}

void User::GroupRemoved(){
    m_isInGroup = false;
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