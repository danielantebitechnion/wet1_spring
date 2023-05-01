#include "Group.h"

Group::Group(int groupID) : m_groupID(groupID), m_viewsAsGroup(new int[GENRE_AMOUNT]),
                            m_groupUsers(), m_totalGroupMembersViews(new int[GENRE_AMOUNT]), m_groupVipCounter(0){}

// Getter for m_groupID
int Group::getGroupID() const {
    return m_groupID;
}

// Getter for m_groupSize
int Group::getGroupSize() const {
    return m_groupUsers.getSize();
}

// Getter for m_viewsAsGroup
int Group::getViewsAsGroupByGenre(Genre genre) const {
    return m_viewsAsGroup[static_cast<int>(genre)];
}

// Setter for m_viewsAsGroup
void Group::setViewsAsGroupByGenre(Genre genre, int viewsAsGroup) {
    m_viewsAsGroup[static_cast<int>(genre)] = viewsAsGroup;
}

// Getter for m_groupUsers
Tree<int, User*>& Group::getGroupUsers() {
    return m_groupUsers;
}

// Getter for m_totalGroupMembersViews
int Group::getTotalGroupMembersViewsByGenre(Genre genre) const {
    return m_totalGroupMembersViews[static_cast<int>(genre)];
}

// Setter for m_totalGroupMembersViews
void Group::setTotalGroupMembersViewsByGenre(Genre genre, int views) {
    m_totalGroupMembersViews[static_cast<int>(genre)] = views;
}

// Getter for m_groupVipCounter
int Group::getGroupVipCounter() const {
    return m_groupVipCounter;
}

// Setter for m_groupVipCounter
void Group::setGroupVipCounter(int groupVipCounter) {
    m_groupVipCounter = groupVipCounter;
}

// Remove user from group and update stats
void Group::removeUserFromGroup(const User& u1){
    if (u1.isVip()){
        this->m_groupVipCounter--;
    }
    for (int i=0;i<4;i++){
        m_totalGroupMembersViews[i] -= u1.getViewsByGenre(static_cast<Genre>(i));
    }
    m_groupUsers.remove(u1.getId());
}

void Group::print() const {
    std::cout << "Group ID: " << m_groupID << std::endl;
    std::cout << "Group size: " << getGroupSize() << std::endl;
    std::cout << "Views as group by genre: ";
    for (int i = 0; i < GENRE_AMOUNT; i++) {
        std::cout << m_viewsAsGroup[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Total group members views by genre: ";
    for (int i = 0; i < GENRE_AMOUNT; i++) {
        std::cout << m_totalGroupMembersViews[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Group VIP counter: " << m_groupVipCounter << std::endl;
}
