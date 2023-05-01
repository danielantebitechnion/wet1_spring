
#include "Movie.h"
#include "StreamingDBa1.h"
#include <iostream>

int main() {
    Movie *adi = new Movie(1, Genre::COMEDY, 5, true);
    Movie *adi1_but_not_vip = new Movie(2, Genre::COMEDY, 5, false);
    Movie *adi3 = new Movie(3, Genre::DRAMA, 0, true);
    Movie *adi4 = new Movie(6, Genre::FANTASY, 9, true);
    Movie *adi5 = new Movie(4, Genre::COMEDY, 12, true);
    Movie *adi6 = new Movie(5, Genre::COMEDY, 12, true);
    Movie *adi7 = new Movie(11, Genre::COMEDY, 12, true);
    Movie *adi8 = new Movie(25, Genre::COMEDY, 12, true);
    Movie *adi9 = new Movie(12311, Genre::COMEDY, 12, true);


}
