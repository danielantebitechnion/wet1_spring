#ifndef DS_1_WET_USER_H
#define DS_1_WET_USER_H
static const int GENRE_AMOUNT = 4;



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
};


#endif //DS_1_WET_USER_H
