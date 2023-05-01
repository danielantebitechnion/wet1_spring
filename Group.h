#ifndef DS_1_WET_GROUP_H
#define DS_1_WET_GROUP_H

#include "User.h"
#include "Tree.h"
static const int EMPTY = 0;

class Group {
private:
    int m_groupID;
    int m_groupSize;
    int* m_viewsAsGroup;
    Tree<int, User*> m_groupUsers;
    int* m_totalGroupMembersViews;
    int m_groupVipCounter;
public:
    Group() = default;
    Group(int groupID);
    ~Group() = default;
};


#endif //DS_1_WET_GROUP_H
