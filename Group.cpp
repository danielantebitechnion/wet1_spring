#include "Group.h"
#include "User.h"

Group::Group(int groupID) : m_groupID(groupID), m_groupVipCounter(0),m_groupUsers(){
    for (int i=0;i<TOTAL_GENRES;i++){
        m_viewsAsGroup[i] = 0;
        m_totalGroupMembersViews[i] = 0;
    }
}

int Group::GroupSize() const {
    return m_groupUsers.getSize();
}

Tree<int,User*>* Group::getGroupUsers() {
    return &m_groupUsers;
}
void Group::addUserToGroup(int id,User* u){
    m_groupUsers.insert(id,u);
}
// Getter for m_groupID
int Group::getGroupID() const {
    return m_groupID;
}

void Group::removeUserFromGroup(int id) {
    m_groupUsers.remove(id);
}

// Getter for m_viewsAsGroup
int Group::getViewsAsGroupByGenre(Genre genre) const {
    return m_viewsAsGroup[static_cast<int>(genre)];
}

// Setter for m_viewsAsGroup
void Group::addViewsAsGroupByGenre(Genre genre, int viewsAsGroup) {
    m_viewsAsGroup[static_cast<int>(genre)] += viewsAsGroup;
}

// Getter for m_totalGroupMembersViews
int Group::getTotalGroupMembersViewsByGenre(Genre genre) const {
    return m_totalGroupMembersViews[static_cast<int>(genre)];
}

// Setter for m_totalGroupMembersViews
void Group::addTotalGroupMembersViewsByGenre(Genre genre, int views) {
    m_totalGroupMembersViews[static_cast<int>(genre)] += views;
}

// Getter for m_groupVipCounter
int Group::getGroupVipCounter() const {
    return m_groupVipCounter;
}

// Setter for m_groupVipCounter
void Group::addGroupVipCounter(int incOrDec) {
    m_groupVipCounter += incOrDec ;
}

void Group::print() const {
    std::cout << "Group ID: " << m_groupID << std::endl;
    std::cout << "Views as group by genre: ";
    for (int i = 0; i < TOTAL_GENRES; i++) {
        std::cout << m_viewsAsGroup[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Total group members views by genre: ";
    for (int i = 0; i < TOTAL_GENRES; i++) {
        std::cout << m_totalGroupMembersViews[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Group VIP counter: " << m_groupVipCounter << std::endl;
}