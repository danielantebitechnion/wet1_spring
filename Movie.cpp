#include "Movie.h"

Movie::Movie(int movieId, Genre genre, int views, bool vipOnly):
        m_movieId(movieId), m_genre(genre), m_views(views), m_vipOnly(vipOnly), m_totalRating(0), m_raterCount(0){
}

int Movie::getMovieId() const {
    return m_movieId;
}

Genre Movie::getGenre() const {
    return m_genre;
}

double Movie::getAverageRating() const {
    return (m_totalRating/m_raterCount);
}

int Movie::getViews() const {
    return m_views;
}

bool Movie::isVipOnly() const {
    return m_vipOnly;
}

void Movie::increaseViews(){
    this->m_views++;
}

void Movie::updateRating(int rating){
    m_raterCount++;
    m_totalRating += rating;
}
