#include "StreamingDBa1.h"
#include <iostream>


streaming_database::streaming_database() : m_allUsers(), m_allGroups(), m_allMovies(),
                                           m_usersByGroup() {
    for(int & i : m_topRatedMovieIdByGenre)
    {
        i = 0;
    }
}

streaming_database::~streaming_database() = default;

void UpdateTopRatedMovieId(AVL_node<GenreTree,int> *node,int *topRatedMovie){
    while(node->getRight() != nullptr){
        node = node->getRight();
    }
    *topRatedMovie = node->getData();
}
StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly) {
    if (movieId <= 0 || genre == Genre::NONE || views < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Movie toAdd = Movie(movieId, genre, views, vipOnly);
        m_allMovies.insert(movieId, toAdd);
        GenreTree newGenreTree = GenreTree(0.0, views, movieId);
        m_treeArrayByGenre[static_cast<int>(genre)].insert(newGenreTree, movieId);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].insert(newGenreTree, movieId);
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(genre)].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(genre)]);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyAlreadyInTree &e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId) {
    if (movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Movie *toDelete = m_allMovies[movieId];
        m_allMovies.remove(movieId);
        GenreTree newGenreTree = GenreTree(toDelete->getAverageRating(), toDelete->getViews(), movieId);
        m_treeArrayByGenre[static_cast<int>(toDelete->getGenre())].remove(newGenreTree);
        m_treeArrayByGenre[GENRE_AMOUNT].remove(newGenreTree);
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(toDelete->getGenre())].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(toDelete->getGenre())]);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip) {
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User toAdd = User(userId, isVip);
        m_allUsers.insert(userId, toAdd);
    } catch (KeyAlreadyInTree &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId) {
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User *u = m_allUsers[userId];
        Group *g = u->getUserGroup();
        if (g != nullptr) { // user has a group
            if (u->isVip()) {
                g->addGroupVipCounter(-1);
            }
            int userViewsPerGenre = 0;
            for (int i = 0; i < GENRE_AMOUNT; ++i) {
                userViewsPerGenre = u->getViewsByGenre(static_cast<Genre>(i));
                g->addTotalGroupMembersViewsByGenre(static_cast<Genre>(i), -userViewsPerGenre);
            }
            m_usersByGroup[g->getGroupID()]->remove(userId);
        }
        m_allUsers.remove(userId);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId) {
    if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Group toAdd = Group(groupId);
        m_allGroups.insert(groupId, toAdd);
        Tree<int, User*> newUserTree;
        m_usersByGroup.insert(groupId, newUserTree);
    } catch (KeyAlreadyInTree &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

void Update_Users_Views(AVL_node<int,User*> *node,int group_views[GENRE_AMOUNT]){
    if(node == nullptr){
        return;
    }
    Update_Users_Views(node->getLeft(),group_views);
    node->getData()->setUserGroup(nullptr);
    int group_views_before_joining;
    for(int i=0;i<GENRE_AMOUNT;i++){
        group_views_before_joining = node->getData()->getViewOfGroupBeforeJoining(static_cast<Genre>(i));
        node->getData()->addViewsByGenre(static_cast<Genre>(i),group_views[i]-group_views_before_joining);
        node->getData()->setViewOfGroupBeforeJoining(static_cast<Genre>(i),0);
    }
    Update_Users_Views(node->getRight(),group_views);

}

StatusType streaming_database::remove_group(int groupId) {
    if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Group *g = m_allGroups[groupId];
        int tempGroupViews[4];
        for (int i = 0; i < GENRE_AMOUNT; ++i) {
            tempGroupViews[i] = g->getViewsAsGroupByGenre(static_cast<Genre>(i));
        }
        m_allGroups.remove(groupId);
        Tree<int, User *> *userTreeInGroup = m_usersByGroup[groupId];
        Update_Users_Views(userTreeInGroup->getRoot(),tempGroupViews);
        m_usersByGroup.remove(groupId);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId) {
    if (userId <= 0 || groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User *u = m_allUsers[userId];
        Group *g = m_allGroups[groupId];
        if (u->getUserGroup() != nullptr) {
            return StatusType::FAILURE;
        }
        u->setUserGroup(g);
        m_usersByGroup[groupId]->insert(userId, u);
        int currGenreViewsUser = 0;
        int groupViewBeforeJoiningGenre = 0;
        for (int i = 0; i < GENRE_AMOUNT; ++i) {
            groupViewBeforeJoiningGenre = g->getViewsAsGroupByGenre(static_cast<Genre>(i));
            u->setViewOfGroupBeforeJoining(static_cast<Genre>(i), groupViewBeforeJoiningGenre);
            currGenreViewsUser = u->getViewsByGenre(static_cast<Genre>(i));
            g->addTotalGroupMembersViewsByGenre(static_cast<Genre>(i), currGenreViewsUser);
        }
        if (u->isVip()) {
            g->addGroupVipCounter(1);
        }
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId) {
    if (userId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User *u = m_allUsers[userId];
        Movie *movie = m_allMovies[movieId];
        if (!u->isVip() && movie->isVipOnly()) {
            return StatusType::FAILURE;
        }
        u->addViewsByGenre(movie->getGenre(), 1);
        if(u->getUserGroup()!= nullptr){
            u->getUserGroup()->addTotalGroupMembersViewsByGenre(movie->getGenre(), 1);
        }
        movie->increaseViews(1);
        Movie newMovie = Movie(movieId, movie->getGenre(), movie->getViews() , movie->isVipOnly());
        remove_movie(movieId);
        add_movie(movieId, newMovie.getGenre(), newMovie.getViews(), newMovie.isVipOnly());
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(movie->getGenre())].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(movie->getGenre())]);
    }
    catch (KeyNotInTree &) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId, int movieId) {
    if (groupId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try{
        Group *group = m_allGroups[groupId];
        int group_size = m_usersByGroup[groupId]->getSize();
        Movie *movie = m_allMovies[movieId];
        if(movie->isVipOnly() && group->getGroupVipCounter()==0 || group_size == 0){
            return StatusType::FAILURE;
        }
        movie->increaseViews(group_size);
        group->addViewsAsGroupByGenre(movie->getGenre(),1);
        Movie newMovie = Movie(movieId, movie->getGenre(), movie->getViews(), movie->isVipOnly());
        remove_movie(movieId);
        add_movie(movieId, newMovie.getGenre(), newMovie.getViews(), newMovie.isVipOnly());
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(movie->getGenre())].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(movie->getGenre())]);
    }
    catch (KeyNotInTree &) {
        return StatusType::FAILURE;
    }catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre) {
    try {
        output_t<int> res(m_treeArrayByGenre[static_cast<int>(genre)].getSize());
        return res;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}
void getMoviesAsSortedArray(AVL_node<GenreTree,int> *node,int *const output,int index){
    if(node == nullptr){
        return;
    }
    getMoviesAsSortedArray(node->getRight(),output,index);
    output[index] = node->getData();
    index++;
    getMoviesAsSortedArray(node->getLeft(),output,index);

}
StatusType streaming_database::get_all_movies(Genre genre, int *const output) {
    try {
        if (output == nullptr) {
            return StatusType::INVALID_INPUT;
        }
        if (m_treeArrayByGenre[static_cast<int>(genre)].getSize() == 0) {
            return StatusType::FAILURE;
        }
        getMoviesAsSortedArray(m_treeArrayByGenre[static_cast<int>(genre)].getRoot(),output,0);
    }catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre) {
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    int sumOfViews = 0;
    try {
        User *u = m_allUsers[userId];
        bool hasGroupFlag = false;
        if (u->getUserGroup() != nullptr) {
            hasGroupFlag = true;
        }
        if (genre == Genre::NONE) {
            for (int i = 0; i < GENRE_AMOUNT; i++) {
                sumOfViews += u->getViewsByGenre(static_cast<Genre>(i));
                if(hasGroupFlag)
                {
                    sumOfViews -= u->getViewOfGroupBeforeJoining(static_cast<Genre>(i));
                    sumOfViews += u->getUserGroup()->getViewsAsGroupByGenre(static_cast<Genre>(i));
                }
            }
        }
        else {
            sumOfViews += u->getViewsByGenre(genre);
            if(hasGroupFlag) {
                sumOfViews -= u->getViewOfGroupBeforeJoining(genre);
                sumOfViews += u->getUserGroup()->getViewsAsGroupByGenre(genre);
            }
        }
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    }
    output_t<int> res(sumOfViews);
    return res;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating) {
    if (userId <= 0 || movieId <= 0 || rating > 100 || rating < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User *u = m_allUsers[userId];
        Movie *movie = m_allMovies[movieId];
        if (!u->isVip() && movie->isVipOnly()) {
            return StatusType::FAILURE;
        }
        GenreTree newGenreTree = GenreTree(movie->getAverageRating(), movie->getViews(), movieId);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].remove(newGenreTree);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].remove(newGenreTree);
        movie->updateRating(rating);
        GenreTree updatedGenreTree = GenreTree(movie->getAverageRating(), movie->getViews(), movieId);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].insert(updatedGenreTree,movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].insert(updatedGenreTree,movieId);
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(movie->getGenre())].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(movie->getGenre())]);
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}



output_t<int> streaming_database::get_group_recommendation(int groupId) {
    if(groupId<=0){
        return  StatusType::INVALID_INPUT;
    }
    try{
        int groupSize = m_usersByGroup[groupId]->getSize();
        if(groupSize == 0){
            return StatusType::FAILURE;
        }
        Group *group = m_allGroups[groupId];
        int mostFavoriteGenreViews = -1;
        int mostFavoriteGenreIndex = -1;
        for(int i=0;i<GENRE_AMOUNT;i++){
            if(group->getTotalGroupMembersViewsByGenre(static_cast<Genre>(i)) > mostFavoriteGenreViews){
                mostFavoriteGenreIndex = i;
            }
        }
        if(m_treeArrayByGenre[mostFavoriteGenreIndex].getSize() == 0){
            return StatusType::FAILURE;
        }
        output_t<int> res(m_topRatedMovieIdByGenre[mostFavoriteGenreIndex]);
        return res;


    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


