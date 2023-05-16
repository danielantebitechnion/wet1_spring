// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "User.h"
#include "Group.h"
#include "Movie.h"
#include "GenreTree.h"

class streaming_database {
private:
    Tree<int, User> m_allUsers; //Tree of all users in DB
    Tree<int, Group> m_allGroups; //Tree of all groups in DB
    Tree<int, Movie> m_allMovies; //Tree of all movies in DB
    Tree<GenreTree, int> m_treeArrayByGenre[GENRE_AMOUNT+1]; //Array of trees by genre
    Tree<int, Tree<int, User*>> m_usersByGroup; //Tree of Trees of groups and their users within the group

public:
	// <DO-NOT-MODIFY> {

    Tree<int, User> getUsersTree()
    {
	    return m_allUsers;
    }

    Tree<int, Group> getGroupTree()
    {
	    return m_allGroups;
    }

    Tree<int, Movie> getAllMovies() const{
	    return m_allMovies;
	}

    Tree<GenreTree, int>* getGenreTree(Genre g)
    {
	    return &m_treeArrayByGenre[static_cast<int>(g)];
    }

    Tree<int, User*> getUserGroupTree(int group)
    {
	    return *m_usersByGroup[group];
    }

	streaming_database();

	virtual ~streaming_database();
	
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);
	
	StatusType remove_movie(int movieId);
	
	StatusType add_user(int userId, bool isVip);
	
	StatusType remove_user(int userId);
	
	StatusType add_group(int groupId);
	
	StatusType remove_group(int groupId);

	StatusType add_user_to_group(int userId, int groupId);
	
	StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);
	
	output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);
	
	output_t<int> get_group_recommendation(int groupId);
	
	// } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
