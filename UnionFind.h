/*
 * UnionFind.h
 * Author: Nang Chen (cs100fao) , Haonan Huang (cs100fbd)
 * Date:   12/01/2017
 *
 * This file is the header file of UnionFind.cpp that implements 
 * union find that finds the connection of actors.
 *
 */


#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "ActorGraph.h"
#include <unordered_map>
#include "ActorNode.h"

class UnionFind{
	protected:
		unordered_map<string, ActorNode*> * ufind_map;
	public:
		//constructor
		UnionFind(unordered_map<string,ActorNode*> *u_map):ufind_map(u_map){}

		/**
 		 * A method to connect the roots of two actors.
 		 */ 	
		void connect(ActorNode* actorA, ActorNode* actorB);
				
		/**
 		 * A method to find the root of the target actor.
 		 */ 		
		ActorNode* find(ActorNode* actor_find);	
};

#endif
