/*
 * ActorNode.h
 * Author: Nang Chen (cs100fao) , Haonan Huang (cs100fbd)
 * Date:   12/01/2017
 *
 * This file is used to implement nodes that are used to hold
 * each actor.
 *
 */

#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <climits>
#include <unordered_map>
#include <vector>
#include "ActorEdge.h"

using namespace std;
// the actor node class
class ActorNode {

public:
	string name;
	string movieName;
	int dist;
	ActorNode* prev;
	vector<ActorEdge*> * edgeList;
	vector<string> * adjList;	
	bool visited;
	vector<string> * movieList;
    	int edge;
	//constructor
	ActorNode(string tempName):name(tempName)
	{
		prev = nullptr;
		edgeList = new vector<ActorEdge*>();
		dist = INT_MAX;
		adjList = new vector<string>();
		movieList = new vector<string>();
        	edge = 0;
	};
};

// the compare method of a priority queue to store ActorNode
// the method will put the smaller distance in the top of the queue
class compareActor {

public:
	bool operator()(ActorNode* actorA,ActorNode* actorB){
	 	if (actorA->dist != actorB->dist){
			return actorA->dist >= actorB->dist;
		}
		else{
			if(actorA->name.compare(actorB->name) != 0){
				return actorA->name.compare(actorB->name) < 0;
			}
		}
        	return false;
    	}
};

#endif // ACTORNODE_H

