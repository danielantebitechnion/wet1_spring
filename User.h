#ifndef DS_1_WET_USER_H
#define DS_1_WET_USER_H
static const int GENRE_AMOUNT = 4;
#include "wet1util.h"
#include <iostream>


class User {
private:
    int m_id;
    bool m_isVip;
    int* m_viewsByGenre;
    int* m_viewOfGroupBeforeJoining;
public:
    User() = default;
    User(int id, bool isVip);
    ~User() = default;
    User(const User& other) = default;
    int getId() const; // Getter for m_id
    bool isVip() const; // Getter for m_isVip
    int getViewsByGenre(Genre genre) const; // Getter for m_viewsByGenre
    void setViewsByGenre(Genre genre, int views); // Setter for m_viewsByGenre
    int getViewOfGroupBeforeJoining(Genre genre) const; // Getter for group views in genere before joining
    void setViewOfGroupBeforeJoining(Genre genre, int views); // Setter for views of group before joining
    void print() const;
};


#endif //DS_1_WET_USER_H