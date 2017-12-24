/*
 * ActorEdge.cpp
 * Author: <Haonan Huang> <Nang Chen>
 * Date:   <12/7/2017>
 *
 * This file is meant to exist as header file for actorEdge
 */
#ifndef ACTOREDGE_H
#define ACTOREDGE_H

#include <iostream>
#include <vector>
#include "ActorNode.h"

using namespace std;

class ActorNode;
class Movie;

//Connect the actor by Edge if they have the same movie.
class ActorEdge
{
public:
	ActorNode* startFrom;
	ActorNode* endAt;
	Movie* movieOf;

	ActorEdge(ActorNode* start,ActorNode* end,Movie* movie):
	startFrom(start),endAt(end),movieOf(movie){
    };
		
};

#endif // ACTOREDGE_H
