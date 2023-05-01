#include "StreamingDBa1.h"
#include <iostream>


streaming_database::streaming_database() : m_allUsers(), m_allGroups(), m_allMovies(),
                                           m_treeArrayByGenre(new Tree<GenreTree, Movie*>[GENRE_AMOUNT+1]), m_usersInGroups()
{
}

streaming_database::~streaming_database()
{
	delete[] m_treeArrayByGenre;
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
	if(movieId <= 0 || genre == Genre::NONE || views < 0)
    {
	    return StatusType::INVALID_INPUT;
    }
    try {
        Movie newMovie = Movie(movieId, genre, views, vipOnly);
        m_allMovies.insert(movieId, newMovie);
        GenreTree newGenreTree = GenreTree(0.0, views, movieId);
        m_treeArrayByGenre[static_cast<int>(genre)].insert(newGenreTree, &newMovie);
    } catch(std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }catch(KeyAlreadyInTree& e){
        std::cout << "hello";
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
	if(movieId <= 0)
    {
	    return StatusType::INVALID_INPUT;
    }
	try{
        Movie* toDelete = m_allMovies.find_by_index(movieId);
        if(toDelete == nullptr)
        {
            return StatusType::FAILURE;
        }
        m_allMovies.remove(movieId);
        GenreTree newGenreTree = GenreTree(toDelete->getAverageRating(), toDelete->getViews(), movieId);
        m_treeArrayByGenre[static_cast<int>(toDelete->getGenre())].remove(newGenreTree);
        m_treeArrayByGenre[static_cast<int>(Genre::NONE)].remove(newGenreTree);
    }catch(std::bad_alloc &e){return StatusType::ALLOCATION_ERROR;}
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if (userId<= 0){
        return StatusType::INVALID_INPUT;
    }
    try{
        User user(userId,isVip);
        m_allUsers.insert(userId,user);
    }catch (KeyAlreadyInTree &e){
        return StatusType::FAILURE;
    }
    catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if (userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    try{
        User* u = m_allUsers.find_by_index(userId);
        if (u == nullptr){
            return StatusType::FAILURE;
        }
        Group *g = *m_usersInGroups.find_by_index(userId);
        if (g != nullptr){ // user has a group
            g->removeUserFromGroup(*u);
            m_usersInGroups.remove(userId); //remove user from users_group tree
        }
        else{ // user exists and isn't part from group
            m_allUsers.remove(userId);
        }
    }catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


