#ifndef Movie_H
#define Movie_H

#include "wet1util.h"

class Movie {
    private:
      int movieId;
      Genre genre;
      double rating; // avarage rating of the movie
      int views; // total views for a movie
      bool vipOnly; // define if only vip users can watch this movie    

Movie() = default;
Movie(int movieId, Genre genre, int views, bool vipOnly);
~Movie() = default;

};
#endif // Movie_H
