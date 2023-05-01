#include "Movie.h"
#include "StreamingDBa1.h"
#include <iostream>

int main() {
    streaming_database sd;
    /*Movie *PiratesOftheCarriebean1 = new Movie(1, Genre::COMEDY, 5, true);
    Movie *PiratesOftheCarriebean2 = new Movie(3, Genre::DRAMA, 0, true);
    Movie *PiratesOftheCarribean3 = new Movie(6, Genre::FANTASY, 9, true);
    Movie *PiratesOftheCarriebean4 = new Movie(4, Genre::COMEDY, 12, true);
    Movie *PiratesOftheCarriebean5 = new Movie(5, Genre::COMEDY, 12, true);
    Movie *HarryPotter1 = new Movie(11, Genre::COMEDY, 12, true);
    Movie *HarryPotter2 = new Movie(25, Genre::COMEDY, 12, true);
    Movie *HarryPotter3 = new Movie(2, Genre::COMEDY, 12, true);
    Movie *HarryPotter4 = new Movie(1, Genre::COMEDY, 12, true);
    Movie *HarryPotter5 = new Movie(12311, Genre::COMEDY, 12, true);
    Movie *HarryPotter6 = new Movie(12311, Genre::COMEDY, 12, true);
    Movie *HarryPotter7 = new Movie(12311, Genre::COMEDY, 12, true);
    Movie *HarryPotter8 = new Movie(12311, Genre::COMEDY, 12, true);*/
    //sd.remove_movie(1);
    sd.add_movie(1, Genre::COMEDY, 0, true);
    sd.returnAllMovies().print();
    sd.add_movie(2,Genre::NONE, 10, false);
    sd.add_movie(5,Genre::COMEDY,5, false);
    sd.add_movie(3,Genre::DRAMA,12, true);
    sd.add_movie(14,Genre::FANTASY, 50, false);
    sd.add_movie(10, Genre::FANTASY, 25, true);
    /*sd.add_movie(1, Genre::ACTION, 0, true);*/
    sd.add_movie(1, Genre::ACTION, 0, true);
    sd.remove_movie(1);
    /*//movie doesnt exist
    sd.remove_movie(15);*/
    //remove all movies
    sd.remove_movie(2);
    sd.remove_movie(5);
    sd.remove_movie(3);
    sd.remove_movie(14);
    sd.remove_movie(10);


}
