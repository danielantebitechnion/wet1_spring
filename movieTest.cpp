#include "Movie.h"
#include "StreamingDBa1.h"
#include <iostream>

int main() {
    streaming_database sd;
    //movie add
    sd.add_movie(1, Genre::COMEDY, 5, true);
    sd.getAllMovies().print();
    std::cout << sd.getAllMovies().find_by_index(1)->getViews();
    sd.getAllMovies().find_by_index(1)->printMovie();

    //user add
    sd.add_user(2, false);
    sd.getUsersTree().print();
    sd.getUsersTree().find_by_index(2)->print();


    //group add
    sd.add_group(3);
    sd.getGroupTree().print();
    sd.getGroupTree().find_by_index(3)->print();

    //add user to group
    sd.add_user_to_group(2, 3);
    sd.getUserGroupTree(3).print();

    //watch and rate
    sd.user_watch(2, 1);
    int views = sd.getAllMovies().find_by_index(1)->getViews();
    std::cout << "View count should be 1, it is:" <<views << std::endl;

    sd.rate_movie(2, 3, 50);
    double rating = sd.getAllMovies().find_by_index(1)->getAverageRating();
    std::cout << "avg rating should be 50, it is:" << rating << std::endl;

    //get count
    int count = sd.getAllMovies().getSize();
    std::cout << "Movies count should be 1, it is: " <<count << std::endl;

    //removing everything from the system
    sd.remove_group(3);
    sd.remove_user(2);
    sd.remove_movie(1);
}
