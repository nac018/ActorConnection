/*
 *  Name: Haonan Huang, Nang Chen
 *  Data: 12/7/2017
 *  Overview: Header file for the Movie
 *  Assignment Number: 4
 */
#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <vector>
#include "ActorNode.h"

using namespace std;


// the movie class to store the movie information
class Movie
{
public:
	string name;
	int year;
    vector<ActorNode*> * actorList;
	Movie(string movieName, int movieYear):name(movieName),year(movieYear)
	{
		actorList = new vector<ActorNode*>;
	};
};

// the compare method of a priority queue to store Movie
// the method will put the earlier movie in the top of the queue
class compareMovie {
    
public:
    bool operator()(Movie* movieA,Movie* movieB){
        if (movieA->year != movieB->year){
            return movieA->year > movieB->year;
        }
        else{
            if(movieA->name.compare(movieB->name) != 0){
                return movieA->name.compare(movieB->name) < 0;
            }
        }
        return false;
    }
    
};



#endif // MOVIE_H
