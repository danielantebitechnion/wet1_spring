#ifndef DS_1_WET_USER_H
#define DS_1_WET_USER_H

static const int GENRE_AMOUNT = 4;

#include "wet1util.h"
#include "Group.h"
#include "AVL_node.h"
#include <iostream>


class User {
private:
    int m_id;
    bool m_isVip;
    int* m_viewsByGenre;
    int* m_viewOfGroupBeforeJoining;
    Group* m_currentGroup;
    AVL_node<int, User*> m_rootOfUserGroup;
public:
    User() = default;
    User(int id, bool isVip);
    ~User() = default;
    User(const User& other) = default;
    int getId() const; // Getter for m_id
    bool isVip() const; // Getter for m_isVip
    int getViewsByGenre(Genre genre) const; // Getter for m_viewsByGenre
    Group* getUserGroup() const;
    void addViewsByGenre(Genre genre, int views); // Setter for m_viewsByGenre
    int getViewOfGroupBeforeJoining(Genre genre) const; // Getter for group views in genere before joining
    AVL_node<int, User*> getRootOfUserGroup() const;
    void setViewOfGroupBeforeJoining(Genre genre, int views); // Setter for views of group before joining
    void setUserGroup(Group* group);
    void setRootOfUserGroup(AVL_node<int, User*> const &user) ;
    void print() const;
};


#endif //DS_1_WET_USER_H