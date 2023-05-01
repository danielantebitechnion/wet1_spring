#ifndef DS_1_WET_GROUP_H
#define DS_1_WET_GROUP_H

#include "User.h"
#include "Tree.h"
static const int EMPTY = 0;

class Group {
private:
    int m_groupID;
    int* m_viewsAsGroup;
    Tree<int, User*> m_groupUsers;
    int* m_totalGroupMembersViews;
    int m_groupVipCounter;
public:
    Group() = default;
    Group(int groupID);
    ~Group() = default;
    Group(const Group& other);
    int getGroupID() const;
    int getGroupSize() const;
    int getViewsAsGroupByGenre(Genre genre) const;
    void setViewsAsGroupByGenre(Genre genre,int viewsAsGroup);
    Tree<int, User*>& getGroupUsers();
    int getTotalGroupMembersViewsByGenre(Genre genre) const;
    void setTotalGroupMembersViewsByGenre(Genre genre, int views);
    int getGroupVipCounter() const;
    void setGroupVipCounter(int groupVipCounter);
    void removeUserFromGroup(const User& u1);
    void print() const;
};


#endif //DS_1_WET_GROUP_H
