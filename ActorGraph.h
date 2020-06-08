#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H


#include <iostream>
#include <unordered_map>
#include <vector>
#include "ActorNode.h"
#include "ActorEdge.h"
#include "Movie.h"

using namespace std;


class ActorGraph {
    protected:

        unordered_map<string, ActorNode*> *ActorMap;
	unordered_map<string, Movie*> *MovieMap;
	
        // Maybe add class data structure(s) here

    public:
        ActorGraph(void);
        int hashFunction(string a);
        long findActor(string a);

        // Maybe add some more methods here

        /** You can modify this method definition as you wish
         *
         * Load the graph from a tab-delimited file of actor->movie 
         * relationships.
         *
         * in_filename - input filename
         *
         * use_weighted_edges - if true, compute edge weights as 
         * 1 + (2015 - movie_year), otherwise all edge weights will be 1
         *
         * return true if file was loaded sucessfully, false otherwise
         */
        bool loadFromFile(const char* in_filename, bool use_weighted_edges);

	/**
         * Load the graph from a tab-delimited file of actor->movie
         * relationships without building the actor edges out. 
         */ 
	bool simpleLoad(const char* in_filename, bool use_weighted_edges);

	/**
         * Print the path to the output file with the given format.
         */
	void printPath(string actor_start, string actor_end, ofstream& outfile);

	/**
 	 * Implement path finder with Breath First Search.
 	 */ 
	void find_BFS(string actor_start, string actor_end);

	/**
 	 * Implement path finder with Dijkstra's Algorithm.
 	 */ 	
	void find_Dijkstra(string actor_start, string actor_end);
	
	/**
 	 * Implement actor connections with Breath First Search.
 	 */	 
	int connect_bfs(string actor_start, string actor_end);

	/**
 	 * Implement actor connections with disjoint set (i.e. Union Find).
 	 */ 
	int connect_ufind(string actor_start, string actor_end);

	/**
 	 * Delete all the created vectors and unordered maps to restore memory.
 	 */ 
	void deleteAll();	
        
    
};


#endif // ACTORGRAPH_H
