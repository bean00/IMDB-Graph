// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!! DO NOT EDIT THIS FILE !!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include "console.h"
#include <iostream>
#include "IMDBData.h"

// Option 1 in Main Menu
void moviesFromActor(IMDBData& data)
{
	std::string actor;
	std::cout << "Enter an actor's name" << std::endl;
	std::cout << ">";
	std::getline(std::cin, actor);

	std::vector<std::string>& movieList = data.getMoviesFromActor(actor);

	if (movieList.size() > 0)
	{
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << actor << " has been in " << movieList.size() << " movies: " << std::endl;
		for (std::string& s : movieList)
		{
			std::cout << s << std::endl;
		}
		std::cout << "--------------------------------------------------" << std::endl;
	}
	else
	{
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << actor << " has no known movies!" << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
	}
}

// Option 2 in Main Menu
void actorsFromMovie(IMDBData& data)
{
	std::string movie;
	std::cout << "Enter a movie title (date)" << std::endl;
	std::cout << ">";
	std::getline(std::cin, movie);

	std::vector<std::string>& actorList = data.getActorsFromMovie(movie);

	if (actorList.size() > 0)
	{
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << movie << " had " << actorList.size() << " actors: " << std::endl;
		for (std::string& s : actorList)
		{
			std::cout << s << std::endl;
		}
		std::cout << "--------------------------------------------------" << std::endl;
	}
	else
	{
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << movie << " is unknown!" << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
	}
}

// Option 3 in Main Menu
void relationship(IMDBData& data)
{
	std::string firstActor;
	std::string secondActor;
	
	std::cout << "Enter the first actor's name" << std::endl;
	std::cout << ">";
	std::getline(std::cin, firstActor);

	std::cout << "Enter the second actor's name" << std::endl;
	std::cout << ">";
	std::getline(std::cin, secondActor);

	std::cout << "--------------------------------------------------" << std::endl;
	data.findRelationship(firstActor, secondActor);
	std::cout << "--------------------------------------------------" << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "Enter an actor file to load" << std::endl;
	std::cout << ">";
	std::string file;
	std::getline(std::cin, file);
	
	std::cout << "Loading file..." << std::endl;
	IMDBData data(file);

	std::cout << "Creating graph..." << std::endl;
	data.createGraph();

	while (true)
	{
		std::cout << "Main Menu" << std::endl;
		std::cout << "1. Get movies from actor" << std::endl;
		std::cout << "2. Get actors from movies" << std::endl;
		std::cout << "3. Find relationship between actors" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cout << ">";
		
		std::string option;
		std::getline(std::cin, option);
		if (option == "1")
		{
			moviesFromActor(data);
		}
		else if (option == "2")
		{
			actorsFromMovie(data);
		}
		else if (option == "3")
		{
			relationship(data);
		}
		else if (option == "4")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else
		{
			std::cout << "Invalid option, please try again." << std::endl;
		}
	}
	return 0;
}
