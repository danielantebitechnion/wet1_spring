#include "Movie.h"
#include <iostream>

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

void Movie::printMovie() const {
    std::cout << "Movie ID: " << m_movieId << std::endl;
    std::cout << "Genre: " << static_cast<int>(m_genre) << std::endl;
    std::cout << "Total rating: " << m_totalRating << std::endl;
    std::cout << "Number of raters: " << m_raterCount << std::endl;
    std::cout << "Total views: " << m_views << std::endl;
    std::cout << "VIP only: " << (m_vipOnly ? "yes" : "no") << std::endl;
}