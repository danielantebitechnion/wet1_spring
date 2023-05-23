
#include "StreamingDBa1.h"
#include <iostream>

int main(){
    streaming_database *sd = new streaming_database();

    sd->add_user(1, true);
    sd->add_user(2, false);
    sd->add_user(3, false);
    sd->add_user(4, false);
    sd->add_user(5, false);

    sd->add_movie(10, Genre::COMEDY, 0, true);
    sd->add_movie(11, Genre::COMEDY, 0, true);
    sd->add_movie(12, Genre::COMEDY, 0, true);
    sd->add_movie(13, Genre::COMEDY, 0, true);
    sd->add_movie(15, Genre::COMEDY, 0, true);

    sd->add_group(100);

    sd->user_watch(1, 10);
    sd->user_watch(1, 10);
    sd->user_watch(1, 10);
    sd->user_watch(1, 10);
    sd->user_watch(1, 10);

    sd->add_user_to_group(2,100);
    sd->add_user_to_group(3,100);
    sd->add_user_to_group(4,100);
    sd->add_user_to_group(5,100);

    sd->group_watch(100, 10);
    sd->add_user_to_group(1, 100);
    sd->group_watch(100, 11);
    sd->group_watch(100, 11);
    sd->group_watch(100, 11);

    sd->rate_movie(1,10, 50);
    sd->rate_movie(1,11, 60);

    int* const x = 0;
    sd->get_group_recommendation(100);
    sd->get_all_movies(Genre::COMEDY, x);
}
