#include "StreamingDBa1.h"
#include <iostream>


streaming_database::streaming_database()
        : m_allUsers(), m_allGroups(), m_allMovies(), m_usersByGroup(),
          m_treeArrayByGenre{} // Initializes all elements to their default value
{
    for (int i = 0; i <= GENRE_AMOUNT; i++) {
        m_treeArrayByGenre[i] = Tree<GenreTree, int>();
    }
    for (int& i : m_topRatedMovieIdByGenre) {
        i = 0;
    }
}
streaming_database::~streaming_database() = default;

static void UpdateTopRatedMovieId(AVL_node<GenreTree,int> *node,int *topRatedMovie){
    if (node != nullptr) {
        while (node->getRight() != nullptr) {
            node = node->getRight();
        }
        *topRatedMovie = node->getData();
    } else {
        *topRatedMovie = 0;
    }
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
        if (toDelete == nullptr){
            return StatusType::FAILURE;
        }
        GenreTree newGenreTree = GenreTree(toDelete->getAverageRating(), toDelete->getViews(), movieId);
        Genre genre = toDelete->getGenre();
        m_treeArrayByGenre[static_cast<int>(genre)].remove(newGenreTree);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].remove(newGenreTree);
        m_allMovies.remove(movieId);
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(genre)].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(genre)]);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
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
        if(u == nullptr){
            return StatusType::FAILURE;
        }
        if (u->isUserInGroup()){
            Group *g = u->getUserGroup();
            if (u->isVip()) {
                g->addGroupVipCounter(-1);
            }
            int userViewsPerGenre = 0;
            for (int i = 0; i < GENRE_AMOUNT; ++i) {
                userViewsPerGenre = u->getViewsByGenre(static_cast<Genre>(i)) + (u->getUserGroup()->getViewsAsGroupByGenre(static_cast<Genre>(i)) - u->getViewOfGroupBeforeJoining(static_cast<Genre>(i))) ;
                g->addTotalGroupMembersViewsByGenre(static_cast<Genre>(i), -1*userViewsPerGenre);
            }
            m_usersByGroup[g->getGroupID()]->remove(userId);
        }
        m_allUsers.remove(userId);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
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

static void Update_Users_Views(AVL_node<int,User*> *node,int group_views[GENRE_AMOUNT]){
    if(node == nullptr){
        return;
    }
    Update_Users_Views(node->getLeft(),group_views);
    node->getData()->setUserGroup(nullptr);
    node->getData()->GroupRemoved();
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
        if(g == nullptr){
            return StatusType::FAILURE;
        }
        int tempGroupViews[4];
        for (int i = 0; i < GENRE_AMOUNT; ++i) {
            tempGroupViews[i] = g->getViewsAsGroupByGenre(static_cast<Genre>(i));
        }
        Tree<int, User *> *userTreeInGroup = m_usersByGroup[groupId];
        Update_Users_Views(userTreeInGroup->getRoot(),tempGroupViews);
        m_usersByGroup.remove(groupId);
        m_allGroups.remove(groupId);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
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
        if (u== nullptr || g == nullptr){
            return StatusType::FAILURE;
        }
        if(u->isUserInGroup()){
            return StatusType::FAILURE;
        }
        u->setUserGroup(g);
        m_usersByGroup[groupId]->insert(userId, u);
        int UserViewsByGenre = 0;
        int GroupWatchViewsByGenreBeforeUserJoined = 0;
        for (int i = 0; i < GENRE_AMOUNT; ++i) {
            GroupWatchViewsByGenreBeforeUserJoined = g->getViewsAsGroupByGenre(static_cast<Genre>(i));
            u->setViewOfGroupBeforeJoining(static_cast<Genre>(i), GroupWatchViewsByGenreBeforeUserJoined);
            UserViewsByGenre = u->getViewsByGenre(static_cast<Genre>(i));
            g->addTotalGroupMembersViewsByGenre(static_cast<Genre>(i), UserViewsByGenre);
        }
        if (m_allUsers[userId]->isVip()) {
            m_allGroups[groupId]->addGroupVipCounter(1);
        }
    }catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
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
        if(u== nullptr || movie == nullptr ){
            return StatusType::FAILURE;
        }
        if((!u->isVip()) && movie->isVipOnly()){
            return StatusType::FAILURE;
        }
        u->addViewsByGenre(movie->getGenre(), 1);
        if(u->isUserInGroup()){
            u->getUserGroup()->addTotalGroupMembersViewsByGenre(movie->getGenre(), 1);
        }
        GenreTree oldStats = GenreTree(movie->getAverageRating(),movie->getViews(),movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].remove(oldStats);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].remove(oldStats);
        movie->increaseViews(1);
        GenreTree newStats = GenreTree(movie->getAverageRating(),movie->getViews(),movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].insert(newStats,movieId);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].insert(newStats,movieId);
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(movie->getGenre())].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(movie->getGenre())]);
    }catch (std::bad_alloc &e) {
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
        Movie *movie = m_allMovies[movieId];
        if (group == nullptr || movie == nullptr){
            return StatusType::FAILURE;
        }
        int group_size = m_usersByGroup[groupId]->getSize();
        if((movie->isVipOnly() && group->getGroupVipCounter()==0) || group_size == 0){
            return StatusType::FAILURE;
        }
        group->addViewsAsGroupByGenre(movie->getGenre(),1);
        group->addTotalGroupMembersViewsByGenre(movie->getGenre(),group_size);
        GenreTree oldStats = GenreTree(movie->getAverageRating(),movie->getViews(),movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].remove(oldStats);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].remove(oldStats);
        movie->increaseViews(group_size);
        GenreTree newStats = GenreTree(movie->getAverageRating(),movie->getViews(),movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].insert(newStats,movieId);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].insert(newStats,movieId);
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(movie->getGenre())].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(movie->getGenre())]);
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
static void getMoviesAsSortedArray(AVL_node<GenreTree,int> *node,int *const output,int& index){
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
        int index = 0;
        getMoviesAsSortedArray(m_treeArrayByGenre[static_cast<int>(genre)].getRoot(),output,index);
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
        if (u == nullptr){
            return StatusType::FAILURE;
        }
        bool hasGroupFlag = false;
        if (u->isUserInGroup()) {
            hasGroupFlag = true;
        }
        if (genre == Genre::NONE) {
            for (int i = 0; i < GENRE_AMOUNT; i++) {
                sumOfViews += u->getViewsByGenre(static_cast<Genre>(i));
                if (hasGroupFlag) {
                    sumOfViews -= u->getViewOfGroupBeforeJoining(static_cast<Genre>(i));
                    sumOfViews += u->getUserGroup()->getViewsAsGroupByGenre(static_cast<Genre>(i));
                }
            }
        } else {
            sumOfViews += u->getViewsByGenre(genre);
            if (hasGroupFlag) {
                sumOfViews -= u->getViewOfGroupBeforeJoining(genre);
                sumOfViews += u->getUserGroup()->getViewsAsGroupByGenre(genre);
            }
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
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
        if (u== nullptr || movie == nullptr ){
            return StatusType::FAILURE;
        }
        if((!u->isVip()) && movie->isVipOnly()){
            return StatusType::FAILURE;
        }
        GenreTree oldStats = GenreTree(movie->getAverageRating(),movie->getViews(),movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].remove(oldStats);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].remove(oldStats);
        movie->updateRating(rating);
        GenreTree newStats = GenreTree(movie->getAverageRating(),movie->getViews(),movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].insert(newStats,movieId);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].insert(newStats,movieId);
        UpdateTopRatedMovieId(m_treeArrayByGenre[static_cast<int>(movie->getGenre())].getRoot(),&m_topRatedMovieIdByGenre[static_cast<int>(movie->getGenre())]);
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
        Group *group = m_allGroups[groupId];
        if(group == nullptr){
            return StatusType::FAILURE;
        }

        int groupSize = m_usersByGroup[groupId]->getSize();
        if(groupSize == 0){
            return StatusType::FAILURE;
        }
        int mostFavoriteGenreViews = -1;
        int mostFavoriteGenreIndex = -1;
        int total_views;
        for(int i=0;i<GENRE_AMOUNT;i++){
            total_views = group->getTotalGroupMembersViewsByGenre(static_cast<Genre>(i));
            if(total_views > mostFavoriteGenreViews){
                mostFavoriteGenreIndex = i;
                mostFavoriteGenreViews = total_views;
            }
        }
        if(mostFavoriteGenreIndex==-1 || m_treeArrayByGenre[mostFavoriteGenreIndex].getSize() == 0){
            return StatusType::FAILURE;
        }
        output_t<int> res(m_topRatedMovieIdByGenre[mostFavoriteGenreIndex]);
        return res;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


