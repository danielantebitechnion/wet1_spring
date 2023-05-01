#ifndef GENRE_TREE_H
#define GENRE_TREE_H

class GenreTree {
private:
    int movieRank;
    int movieViews;
    int movieId;

public:
    GenreTree(int rank, int views, int id): movieRank(rank),movieViews(views),movieId(id) {}

    bool operator>(const GenreTree &rhs) const {
        if (movieRank > rhs.movieRank)
            return true;
        if (movieViews > rhs.movieViews)
            return true;
        return movieId < rhs.movieId;
    }

    bool operator<(const GenreTree &rhs) const {
        return rhs > *this;
    }
};

#endif //
