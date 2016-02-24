// ITP 365 Fall 2014
// HW7 - IMDB Graph
// Name: Jon Chin
// Email: jonchin@usc.edu
// Platform: Mac
//
// IDMBData.h - Defines IMDBData interface
//
#pragma once
#include <string>
#include "hashmap.h"
#include "IMDBGraph.h"

class IMDBData
{
public:
	// Function: Default Constructor
	// Purpose: Loads in the actor/movie file specified,
	// and populates the data into the appropriate hash maps.
	// Also constructs the graph with actor relationships.
	// Input: Name of file to load (by reference)
	// Returns: Nothing
	IMDBData(const std::string& fileName);

	// Function: reverseMap
	// Purpose: This is a helper function that is used to generate
	// the reverse map (movies to actors)
	// Input: Name of actor (by reference), vector of their movies (by reference)
	// Returns: Nothing
	void reverseMap(const std::string& actorName, const std::vector<std::string>& movies);

	// Function: getMoviesFromActor
	// Purpose: Given an actor's name, returns a vector containing their movies
	// Input: Name of actor (by reference)
	// Returns: Vector of movies (by reference)
	std::vector<std::string>& getMoviesFromActor(const std::string& actorName);
	
	// Function: getActorsFromMovie
	// Purpose: Given a movie's name, returns the name of its actors
	// Input: Name of movie (by reference)
	// Returns: Vector of actors (by reference)
	std::vector<std::string>& getActorsFromMovie(const std::string& movieName);

	// Function: createGraph
	// Purpose: This helper function constructs the IMDBGraph from the movie to actors map
	// Input: None
	// Returns: Nothing
	void createGraph();

	// Function: findRelationship
	// Purpose: Tries to find a relationship between two actors, using a BFS
	// and outputs (to cout) the result of the search.
	// Input: Name of two actors to check for a relationship
	// Returns: Nothing
	void findRelationship(const std::string& fromActor, const std::string& toActor);

private:
	// Hash map which associates an actor with a vector of movies
	HashMap<std::string, std::vector<std::string>> mActorsToMoviesMap;
	
	// Hash map which associates a movie with a vector of actors
	HashMap<std::string, std::vector<std::string>> mMovieToActorsMap;

	// Graph that shows relationships between actors
	IMDBGraph mGraph;

	// Static helper variable used to have an empty vector
	static std::vector<std::string> sEmptyVector;
};
