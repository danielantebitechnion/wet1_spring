#include "Group.h"

Group::Group(int groupID) : m_groupID(groupID), m_groupSize(EMPTY), m_viewsAsGroup(new int[GENRE_AMOUNT]),
                            m_groupUsers(), m_totalGroupMembersViews(new int[GENRE_AMOUNT]), m_groupVipCounter(0){}