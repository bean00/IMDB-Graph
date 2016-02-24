// ITP 365 Fall 2014
// HW7 - IMDB Graph
// Name: Jon Chin
// Email: jonchin@usc.edu
// Platform: Mac
//
// IDMBData.cpp - Implements IMDBData interface
//
#include "IMDBData.h"
#include "queue.h"
#include <fstream>

// Function: Default Constructor
// Purpose: Loads in the actor/movie file specified,
// and populates the data into the appropriate hash maps.
// Also constructs the graph with actor relationships.
// Input: Name of file to load (by reference)
// Returns: Nothing
IMDBData::IMDBData(const std::string& fileName)
{
    // generate the actor to movies map
    // open the file "filename" for input
    std::ifstream fileInput1(fileName);
    
    // create a vector to store movie names
    std::vector<std::string> movieNames;
    
    // create strings to use later
    std::string entireLine;
    std::string actor;
    std::string movie;
    
    // populate mActorsToMoviesMap
    if (fileInput1.is_open())
    {
        while (fileInput1.eof() != true)
        {
            // get a line
            std::getline(fileInput1, entireLine);
            
            // if entireLine is an actor
            if (entireLine[0] != '|')
            {
                actor = entireLine;
                mActorsToMoviesMap.put(actor, movieNames);
            }
            else
            {
                mActorsToMoviesMap[actor].push_back(entireLine.substr(1));
            }
        }
    }
    else
    {
        error("The file does not exist. Sorry :(");
    }
    
    // generate the movie to actors map
    // call reverseMap on each actor to movie vector pair
    for (const std::string& actor : mActorsToMoviesMap) // for-each loop
    {
        reverseMap(actor, mActorsToMoviesMap[actor]);
    }
}

// Function: reverseMap
// Purpose: This is a helper function that is used to generate
// the reverse map (movies to actors)
// Input: Name of actor (by reference), vector of their movies (by reference)
// Returns: Nothing
void IMDBData::reverseMap(const std::string& actorName, const std::vector<std::string>& movies)
{
    for (const std::string& movie : movies) // for-each loop
    {
        // if mMovieToActorsMap contains the movie
        if (mMovieToActorsMap.containsKey(movie))
        {
            // add actoName to the movie's vector
            mMovieToActorsMap[movie].push_back(actorName);
        }
        else
        {
            // add an entry in mMovieToActorsMap that associates the movie
            // with a vector that contains actorName
            std::vector<std::string> actors;
            actors.push_back(actorName);
            
            mMovieToActorsMap.put(movie, actors);
        }
    }
}

// Function: getMoviesFromActor
// Purpose: Given an actor's name, returns a vector containing their movies
// Input: Name of actor (by reference)
// Returns: Vector of movies (by reference)
std::vector<std::string>& IMDBData::getMoviesFromActor(const std::string& actorName)
{
    // if the actor to movies map contains the actorName key specified...
    if (mActorsToMoviesMap.containsKey(actorName))
    {
        return mActorsToMoviesMap[actorName]; // return the lookup
    }
    else
    {
        return sEmptyVector;
    }
}

// Function: getActorsFromMovie
// Purpose: Given a movie's name, returns the name of its actors
// Input: Name of movie (by reference)
// Returns: Vector of actors (by reference)
std::vector<std::string>& IMDBData::getActorsFromMovie(const std::string& movieName)
{
    // if the movie to actors map contains the movieName key specified...
    if (mMovieToActorsMap.containsKey(movieName))
    {
        return mMovieToActorsMap[movieName];
    }
    else
    {
        return sEmptyVector;
    }
}

// Function: findRelationship
// Purpose: Tries to find a relationship between two actors, using a BFS
// and outputs (to cout) the result of the search.
// Input: Name of two actors to check for a relationship
// Returns: Nothing
void IMDBData::findRelationship(const std::string& fromActor, const std::string& toActor)
{
	// check that the two actors are in the graph
    if (!mGraph.containsActor(fromActor))
    {
        std::cout << "Sorry! fromActor is not in the graph. :(" << std::endl;
    }
    if (!mGraph.containsActor(toActor))
    {
        std::cout << "Sorry! toActor is not in the graph. :(" << std::endl;
    }
    
    // get fromActor node
    ActorNode* fromActorNode = mGraph.getActorNode(fromActor);
    
    // get toActor node
    ActorNode* toActorNode = mGraph.getActorNode(toActor);
    
    // declare a queue of ActoreNodes*s
    Queue<ActorNode*> actorNodeQueue;
    
    // enqueue fromActor node
    actorNodeQueue.enqueue(fromActorNode);
    
    // declare a bool pathFound and set to false
    bool pathFound = false;
    
    // while the BFS queue is not empty...
    while (!actorNodeQueue.isEmpty())
    {
        // dequeue the front node, and save in currentNode
        ActorNode* currentNode = actorNodeQueue.dequeue();
        
        // IF currentNode is the target node, we found a path!
        if (currentNode->mName == toActor)
        {
            pathFound = true;
            break;
        }
        // OTHERWISE if currentNode's visited bool is false...
        else if (currentNode->mIsVisited == false)
        {
            // set currentNode's visited bool to true
            currentNode->mIsVisited = true;
            
            // loop through currentNode's adjacency list
            for (Edge* e : currentNode->mEdges)
            {
                // grab the otherActor from the edge
                ActorNode* otherActor = e->mOtherActor;
                
                // if the visited flag is false...
                if (otherActor->mIsVisited == false)
                {
                    // enqueue the adjacent node
                    actorNodeQueue.enqueue(e->mOtherActor);
                    
                    // if the adjacent node path has a size of 0...
                    if (otherActor->mPath.size() == 0)
                    {
                        // set the adjacent node's path equal to the currentNode's path
                        otherActor->mPath = currentNode->mPath;
                        
                        PathPair newPathPair = PathPair(e->mMovieName, otherActor->mName);
                        
                        // Push_back adjacent node's name to adjacent node's path
                        otherActor->mPath.push_back(newPathPair);
                    }
                }
            }
        }
    }
    
    if (pathFound)
    {
        std::cout << "Found a path! Yay! :D" << std::endl;
        std::cout << fromActor << " was in..." << std::endl;
        
        // store the last PathPair in lastPair
        PathPair lastPair = toActorNode->mPath.back();
        // remove the last PathPair from the mPath list
        toActorNode->mPath.pop_back();
        
        for (PathPair p : toActorNode->mPath)
        {
            std::cout << p.getMovieName() << " with " << p.getActorName()
                      << " who was in..." << std::endl;
        }
        
        std::cout << lastPair.getMovieName() << " with " << lastPair.getActorName() << std::endl;
    }
    else
    {
        std::cout << "Didn't find a path. :(" << std::endl;
    }
    
	// LEAVE THIS AT THE END OF THE FUNCTION
	mGraph.clearVisited();
}

// Function: createGraph
// Purpose: This helper function constructs the IMDBGraph from the movie to actors map
// Input: None
// Returns: Nothing
void IMDBData::createGraph()
{
	// DO NOT EDIT THIS FUNCTION
	// For every movie in the actors map...
	for (const std::string& movieName : mMovieToActorsMap)
	{
		// Get the actors for this movie
		const std::vector<std::string>& actors = mMovieToActorsMap[movieName];

		// Make n^2 edges between these actors
		for (size_t i = 0; i < actors.size(); i++)
		{
			ActorNode* firstActor = mGraph.getActorNode(actors[i]);
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				ActorNode* secondActor = mGraph.getActorNode(actors[j]);
				mGraph.createActorEdge(firstActor, secondActor, movieName);
			}
		}
	}
}

std::vector<std::string> IMDBData::sEmptyVector;
