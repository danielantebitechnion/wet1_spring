#ifndef DS_1_WET_GENRETREE_H
#define DS_1_WET_GENRETREE_H

#ifndef GENRE_TREE_H
#define GENRE_TREE_H

class GenreTree {
private:
    double m_movieRating;
    int m_movieViews;
    int m_movieId;

public:
    GenreTree(double rating, int views, int id): m_movieRating(rating), m_movieViews(views), m_movieId(id) {}

    bool operator>(const GenreTree &rhs) const {
        if (m_movieRating > rhs.m_movieRating) {
            return true;
        }
        if(m_movieRating < rhs.m_movieRating){
            return false;
        }
        if (m_movieViews > rhs.m_movieViews) {
            return true;
        }
        if(m_movieViews < rhs.m_movieViews){
            return false;
        }
        return m_movieId < rhs.m_movieId;
    }

    bool operator<(const GenreTree &rhs) const {
        return rhs > *this;
    }

    bool operator==(const GenreTree& rhs) const{
        return m_movieId == rhs.m_movieId &&
        m_movieViews == rhs.m_movieViews &&
        m_movieRating == rhs.m_movieRating;
    }
};

#endif //

#endif //DS_1_WET_GENRETREE_H
