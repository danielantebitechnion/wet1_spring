#include "StreamingDBa1.h"
#include <iostream>


streaming_database::streaming_database() : m_allUsers(), m_allGroups(), m_allMovies(),
                                           m_usersByGroup() {
}

streaming_database::~streaming_database() {

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
                int vipCnt = g->getGroupVipCounter();
                g->addGroupVipCounter(-1);
            }
            int userViewsPerGenre = 0;
            int totalGroupViewsPerGenre = 0;
            for (int i = 0; i < GENRE_AMOUNT; ++i) {
                totalGroupViewsPerGenre = g->getTotalGroupMembersViewsByGenre(static_cast<Genre>(i));
                userViewsPerGenre = u->getViewsByGenre(static_cast<Genre>(i));
                g->addTotalGroupMembersViewsByGenre(static_cast<Genre>(i), totalGroupViewsPerGenre - userViewsPerGenre);
            }
            u->getRootOfUserGroup().remove(u->getId());
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
    } catch (KeyAlreadyInTree &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
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
        if(m_usersByGroup[groupId] == nullptr)
        {
            Tree<int, User*> newUserTree;
            m_usersByGroup.insert(groupId, newUserTree);
        }
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
        if (u->isVip() == false && movie->isVipOnly()) {
            return StatusType::FAILURE;
        }
        u->addViewsByGenre(movie->getGenre(), 1);
        u->getUserGroup()->addTotalGroupMembersViewsByGenre(movie->getGenre(), 1);
        Movie *newMovie = new Movie(movieId, movie->getGenre(), movie->getViews() + 1, movie->isVipOnly());
        remove_movie(movieId);
        add_movie(movieId, newMovie->getGenre(), newMovie->getViews(), newMovie->isVipOnly());
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

    try {
        /*we want to inorder the group<->user tree and call user_watch everytime
         * we want to add the views to the movie(tree size)
         * remove the movie from the genre tree
         * add the movie with the new watch numbers to the genre tree*/
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
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

StatusType streaming_database::get_all_movies(Genre genre, int *const output) {
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre) {
    // TODO: Your code goes here
    return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating) {
    if (userId <= 0 || movieId <= 0 || rating > 100 || rating < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        User *u = m_allUsers[userId];
        Movie *movie = m_allMovies[movieId];
        if (u->isVip() == false && movie->isVipOnly()) {
            return StatusType::FAILURE;
        }
        GenreTree newGenreTree = GenreTree(movie->getAverageRating(), movie->getViews(), movieId);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].remove(newGenreTree);
        m_treeArrayByGenre[GENRE_AMOUNT].remove(newGenreTree);
        m_allMovies[movieId]->updateRating(rating);
        m_treeArrayByGenre[static_cast<int>(movie->getGenre())].insert(newGenreTree, movieId);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].insert(newGenreTree, movieId);
    } catch (KeyNotInTree &e) {
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}



output_t<int> streaming_database::get_group_recommendation(int groupId) {
    // TODO: Your code goes here
    static int i = 0;
    return (i++ == 0) ? 11 : 2;
}


