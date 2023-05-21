#ifndef DS_1_WET_GROUP_H
#define DS_1_WET_GROUP_H

#include "wet1util.h"
#include "Tree.h"
static const int EMPTY = 0;
static const int TOTAL_GENRES = 4;

class Group {
private:
    int m_totalGroupMembersViews[TOTAL_GENRES];
    int m_groupID;
    int m_viewsAsGroup[TOTAL_GENRES];
    int m_groupVipCounter;
public:
    Group() = default;
    Group(int groupID);
    ~Group() = default;
    Group(const Group& other) = default;
    int getGroupID() const;
    int getViewsAsGroupByGenre(Genre genre) const;
    void addViewsAsGroupByGenre(Genre genre,int viewsAsGroup);
    int getTotalGroupMembersViewsByGenre(Genre genre) const;
    void addTotalGroupMembersViewsByGenre(Genre genre, int views);
    int getGroupVipCounter() const;
    void addGroupVipCounter(int incOrDec);
    void print() const;
};


#endif //DS_1_WET_GROUP_H