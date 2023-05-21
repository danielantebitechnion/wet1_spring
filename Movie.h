#ifndef DS_1_WET_MOVIE_H
#define DS_1_WET_MOVIE_H

#include "wet1util.h"

class Movie {
private:
    int m_movieId;
    Genre m_genre;
    int m_totalRating; // sum of all ratings
    int m_raterCount; // amount of watchers that rated the movie
    int m_views; // total views for a movie
    bool m_vipOnly; // define if only vip users can watch this movie
public:
    Movie() = default;
    Movie(int movieId, Genre genre, int views, bool vipOnly);
    ~Movie() = default;
    int getMovieId() const;
    Genre getGenre() const;
    double getAverageRating() const;
    int getViews() const;
    bool isVipOnly() const;
    void increaseViews(int views);
    void updateRating(int rating);
    void printMovie() const;
};

#endif //DS_1_WET_MOVIE_H
