#include "Movie.h"
#include "StreamingDBa1.h"


int main() {

    /*------------------------CREATING USERS-------------------------*/
    streaming_database *sd = new streaming_database();
    sd->add_user(1, true);
    sd->add_user(2, false);

    std::cout << "--------------MOVIE TESTING------------" << std::endl;
    sd->add_movie(1, Genre::COMEDY, 4, true);
    sd->add_movie(10, Genre::COMEDY, 40, true);
    sd->add_movie(100, Genre::COMEDY, 400, true);
    sd->add_movie(2,Genre::DRAMA,5, true);
    sd->add_movie(20,Genre::DRAMA,50, true);
    sd->add_movie(200,Genre::DRAMA,500, true);
    sd->remove_movie(1);
    sd->add_movie(3,Genre::FANTASY,0, true);
    sd->remove_movie(2);
    sd->add_movie(1, Genre::COMEDY, 0, true);
    sd->add_movie(5, Genre::COMEDY, 0, true);
    sd->add_movie(8,Genre::DRAMA,0, true);
    sd->remove_movie(3);
    sd->remove_movie(5);
    std::cout << "--------------GROUP TESTING------------" << std::endl;
    sd->add_group(1);
    sd->add_group(2);
    sd->add_group(3);
    sd->add_user_to_group(1,1);
    sd->add_user_to_group(2,1);
    sd->user_watch(1, 1);
    if(sd->add_user_to_group(2,1) != StatusType::SUCCESS)
    {
        std::cout << "2 couldnt watch vip movie" << std::endl;
    }
    sd->rate_movie(1, 1, 50);
    sd->getGroupTree().print();
}
