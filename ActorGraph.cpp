/*
 * ActorGraph.cpp
 * Author: Nang Chen (cs100fao) , Haonan Huang (cs100fbd)
 * Date:   12/01/2017
 *
 * This file is meant to exist as a container for starter code that 
 * you can use to read the input file format defined in movie_casts.tsv. 
 * Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include "ActorGraph.h"
#include "UnionFind.h"

#define year_DNE 9999

using namespace std;

ActorGraph::ActorGraph(void) {
	ActorMap = new unordered_map<string,ActorNode*>;
	MovieMap = new unordered_map<string,Movie*>;
}


bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
	// Initialize the file stream
	ifstream infile(in_filename);

	bool have_header = false;
	ActorNode* actor;
	Movie* movie;

	// keep reading lines until the end of file is reached
	while (infile) {
		string s;
		//actorNodeExited = false;

		// get the next line
		if (!getline( infile, s )) break;


		if (!have_header) {
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> record;

		while (ss) {
			string next;

			// get the next string before hitting a tab character 
			// and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		if (record.size() != 3) {
			// we should have exactly 3 columns
			continue;
		}
		
		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);
		string movieWithYear= movie_title + to_string(movie_year);

		auto actor_itr = ActorMap->find(actor_name);
		
		//create new actor nodes to build the actor map
		if(actor_itr == ActorMap->end()){
			actor = new ActorNode(actor_name);
			ActorMap->insert(make_pair(actor_name, actor));
		}
		else{
			actor = actor_itr->second;
		}

		//create new movie nodes to build the movie map
		auto movie_itr = MovieMap->find(movieWithYear);

		if(movie_itr == MovieMap->end()){
			movie = new Movie(movie_title,movie_year);
			MovieMap->insert(make_pair(movieWithYear, movie));
		}
		else{
			movie = movie_itr->second;	
		}

		//without duplicate input
		movie->actorList->push_back(actor);
		actor->movieList->push_back(movieWithYear);
	}

	for(auto itr = ActorMap->begin();itr != ActorMap->end();itr++){
		actor = itr->second;
		long movieSize = actor->movieList->size();

		for (int k=0; k< movieSize; k++) {
			//get movie from the movie list of actor
			string tempMovieName =actor->movieList->at(k);
			movie = MovieMap->at(tempMovieName);

			for(int i=0;i<movie->actorList->size();i++){	
				bool actorInAdj = false;
				if(movie->actorList->at(i)->name == actor->name){
                                         actorInAdj = true;
                                }
				for(int j=0;j<actor->adjList->size();j++){
				//check if actor list of specfic movie has the same actor
					if(movie->actorList->at(i)->name == actor->adjList->at(j)){
						actorInAdj = true;
					}
					if(movie->actorList->at(i)->name == actor->name){
						actorInAdj = true;
					}

				}
				//if actor not found
				if(!actorInAdj){
					actor->adjList->push_back(movie->actorList->at(i)->name);
					actor->edge++;
					//create new edge with actors
					ActorEdge *newEdge = new
						ActorEdge(actor, movie->actorList->at(i), movie);
					actor->edgeList->push_back(newEdge);
					movie->actorList->at(i)->edgeList->push_back(newEdge);
				}
			}

		}

	}

	//file reaches the end
	if (!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}

//Return the actor's adjlist size
long ActorGraph::findActor(string a) {

    long tempnum =ActorMap->at(a)->adjList->size();
    return tempnum;
}

//similar to loadFromFile without building edges
bool ActorGraph::simpleLoad(const char* in_filename, bool use_weighted_edges) {
	// Initialize the file stream
	ifstream infile(in_filename);

	bool have_header = false;
	ActorNode* actor;
	Movie* movie;

	// keep reading lines until the end of file is reached
	while (infile) {
		string s;
		//actorNodeExited = false;

		// get the next line
		if (!getline( infile, s )) break;

		if (!have_header) {
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> record;

		while (ss) {
			string next;

			// get the next string before hitting a tab character 
			// and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		if (record.size() != 3) {
			// we should have exactly 3 columns
			continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);
		string movieWithYear= movie_title + to_string(movie_year);

		
		auto actor_itr = ActorMap->find(actor_name);

		if(actor_itr == ActorMap->end()){
			actor = new ActorNode(actor_name);
			ActorMap->insert(make_pair(actor_name, actor));
		}
		else{
			actor = actor_itr->second;
		}
		auto movie_itr = MovieMap->find(movieWithYear);

		if(movie_itr == MovieMap->end()){
			movie = new Movie(movie_title,movie_year);
			MovieMap->insert(make_pair(movieWithYear, movie));
		}
		else{
			movie = movie_itr->second;	
		}

		//without duplicate input
		movie->actorList->push_back(actor);
		actor->movieList->push_back(movieWithYear);
	}

	if (!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();

	return true;
}

void ActorGraph::printPath(string actor_start, string actor_end, 
		ofstream& outfile){
	vector<ActorNode*> reversedPath;
	
	//make a actor node with the ending actor
	ActorNode* endNode = ActorMap->at(actor_end);

	//push the actor node into vector from end to start
	while(endNode->name.compare(actor_start) != 0){	
		reversedPath.push_back(endNode);
		endNode = endNode->prev;
	}
	//reverse the vector into the order from start to end
	reverse(reversedPath.begin(),reversedPath.end());
	vector<ActorNode*> path = reversedPath;
	
	//write the path with the given format
	for (int i = 0; i< (int)path.size(); i++){
		outfile << "[" + path[i]->movieName + "]-->";	
		outfile << "(" + path[i]->name +")";
		if(path[i]->name != actor_end){
			outfile << "--";
		}
	}
	outfile << endl;
}

void ActorGraph::find_BFS(string actor_start, string actor_end){
	ActorNode* clearNode;
	ActorNode* neighbor;
	Movie* movie;

	//make actor nodes with initial values throughout the actor map
	for(auto itr = ActorMap->begin();itr != ActorMap->end();++itr){
		clearNode = itr->second;
		clearNode->prev = nullptr;
		clearNode->dist = INT_MAX;
		clearNode->visited = false;
	}

	//if starting actor is not found
	if (ActorMap->find(actor_start) == ActorMap->end()){
		cout << "Starting actor is not in the graph!!!" << endl;
		return ;
	}

	//if ending actor is not found
	if (ActorMap->find(actor_end) == ActorMap->end()){
		cout << "Ending actor is not in the graph!!!" << endl;
		return;
	}
	
	//start from starting actor and push it to queue
	ActorNode* current = ActorMap->find(actor_start)->second;
	current->dist = 0;
	current->prev = nullptr;
	current->visited = false;
	queue<ActorNode*> queue_bfs;
	queue_bfs.push(current);

	while(!queue_bfs.empty()){
		//dequeue the first element in the queue
		ActorNode* topNode = queue_bfs.front();
		queue_bfs.pop();
		for(vector<ActorEdge*>::iterator itr = topNode->edgeList->begin();
			itr != topNode->edgeList->end(); ++itr){
			neighbor = (*itr)->endAt;
			movie = (*itr)->movieOf;
			
			//if neighbor node has default values
			if(neighbor->prev == nullptr && neighbor->dist == INT_MAX){
				neighbor->prev = topNode;
				//increment distance 
				neighbor->dist = 1 + topNode->dist;
				neighbor->movieName = movie->name + "#@" 
					+ to_string(movie->year);
			}
			//if neighbor has the same name of ending actor
			if (neighbor->name == actor_end) {
				return;
			}
			queue_bfs.push(neighbor);
		}
		if (neighbor->name == actor_end) {
			return;
		}
	}



}

void ActorGraph::find_Dijkstra(string actor_start, string actor_end){
	ActorNode* clearNode;
	ActorNode* neighbor;
	Movie* movie;

	//make actor nodes with initial values throughout the actor map
	for(auto itr = ActorMap->begin();itr != ActorMap->end();++itr){
		clearNode = itr->second;
		clearNode->prev = nullptr;
		clearNode->dist = INT_MAX;
		clearNode->visited = false;
	}

	//if starting actor is not found
	if (ActorMap->find(actor_start) == ActorMap->end()){
		cout << "Starting actor is not in the graph!!!" << endl;
		return;
	}

	//if ending actor is not found
	if (ActorMap->find(actor_end) == ActorMap->end()){
		cout << "Ending actor is not in the graph!!!" << endl;
		return;
	}

	//start from starting actor and push it to priority queue
	ActorNode* current = ActorMap->find(actor_start)->second;
	current->dist = 0;
	current->prev = nullptr;
	current->visited = false;
	priority_queue<ActorNode*,vector<ActorNode*>,compareActor> pq_dijkstra;
	pq_dijkstra.push(current);

	while(!pq_dijkstra.empty()){
		//start with the node with the top priority
		ActorNode* topNode = pq_dijkstra.top();
		pq_dijkstra.pop();
		//if the node is not visited and it's not equal to the ending actor
		if(topNode->visited == false && topNode->name != actor_end){
			topNode->visited = true;
			for(vector<ActorEdge*>::iterator itr=topNode->edgeList->begin(); 
					itr!=topNode->edgeList->end();++itr){
				neighbor = (*itr)->endAt;
				movie = (*itr)->movieOf;
				//total distance
				int distance = topNode->dist + (2015 - movie->year) + 1;
				
				//compare total distance first to get the best path
				if(distance < neighbor->dist)
				{
					neighbor->dist = distance;
					neighbor->prev = topNode;
					neighbor->movieName = movie->name + "#@"
						+ to_string(movie->year);
					if(!neighbor->visited)
						pq_dijkstra.push(neighbor);
				}
			}
		}
	}
}


int ActorGraph::connect_bfs(string actor_start,string actor_end){
	ActorNode* clearNode;
	ActorNode* neighbor;
	Movie* movie;
	priority_queue<Movie*,vector<Movie*>,compareMovie> pq_movie;
	int connectedYear;

	//make all the nodes to their initial values and clear their edge lists
	for(auto itr = ActorMap->begin();itr != ActorMap->end(); ++itr){
		clearNode = itr->second;
		clearNode->prev = nullptr;
		clearNode->dist = INT_MAX;
		clearNode->visited = false;
		clearNode->edgeList->clear();
	}

	//push all the movies into the priority queue
	for (auto itr = MovieMap->begin();itr != MovieMap->end(); ++itr){
		pq_movie.push(itr->second);
	} 

	//if starting actor is not found
	if (ActorMap->find(actor_start) == ActorMap->end()){
		cout << "Starting actor is not in the graph!!!" << endl;
		return year_DNE;
	}

	//if ending actor is not found
	if (ActorMap->find(actor_end) == ActorMap->end()){
		cout << "Ending actor is not in the graph!!!" << endl;
		return year_DNE;
	}

	while (!pq_movie.empty()){
		Movie* movieNode = pq_movie.top();
		pq_movie.pop();
		//use nested loops to create edges with actors in the same actor list
		for(int i = 0; i < (int)movieNode->actorList->size();i++){
			for(int j = 0; j < (int)movieNode->actorList->size();j++){
				if((*(movieNode->actorList))[i] != (*(movieNode->actorList))[j]){
					ActorEdge* connector = new ActorEdge((*(movieNode->actorList))[i]
							,(*(movieNode->actorList))[j],movieNode);
					//push the edges into the edge list of the actor
					(*(movieNode->actorList))[i]->edgeList->push_back(connector);
				}
			}
		}
		//if year of next movie node is the same and the pq is not empty
		if(!pq_movie.empty() && movieNode->year == pq_movie.top()->year){
			continue;
		} 
		

		//***********same algorithm did in find_bfs************
		for(auto itr = ActorMap->begin();itr != ActorMap->end(); ++itr){
			clearNode = itr->second;
			clearNode->prev = nullptr;
			clearNode->dist = INT_MAX;
			clearNode->visited = false;
		}

		ActorNode* current = ActorMap->find(actor_start)->second;
		current->dist = 0;
		current->prev = nullptr;
		current->visited = false;

		queue<ActorNode*> queue_bfs;
		queue_bfs.push(current);

		while(!queue_bfs.empty()){
			ActorNode* topNode = queue_bfs.front();
			queue_bfs.pop();

			for(vector<ActorEdge*>::iterator itr = topNode->edgeList->begin(); 
					itr != topNode->edgeList->end(); ++itr){
				neighbor = (*itr)->endAt;
				movie = (*itr)->movieOf;

				if(neighbor->dist == INT_MAX && neighbor->visited == false){
					queue_bfs.push(neighbor);
				}

				neighbor->visited = true;

				if(neighbor->dist == INT_MAX){
					neighbor->dist = topNode->dist + 1;
					if(neighbor->name == actor_end){
						return movieNode->year;
					}
				}
			} 
		}
	}	
	return connectedYear;
}

int ActorGraph::connect_ufind(string actor_start,string actor_end){
	ActorNode* clearNode;
	ActorNode* neighbor;
	Movie* movie;
	ActorNode* temp =ActorMap->find(actor_start)->second;
   	ActorNode* tempEnd = ActorMap->find(actor_end)->second;
	priority_queue<Movie*,vector<Movie*>,compareMovie> pq_movie;
	int connectedYear;
	UnionFind * u = new UnionFind(ActorMap);

	for(auto itr = ActorMap->begin();itr != ActorMap->end(); ++itr){
		clearNode = itr->second;
		clearNode->prev = nullptr;
		clearNode->dist = INT_MAX;
		clearNode->visited = false;
	}
	//push the movie nodes into the priority queue
	for (auto itr = MovieMap->begin();itr != MovieMap->end(); ++itr){
		pq_movie.push(itr->second);
	} 

	//starting actor is not found
	if (ActorMap->find(actor_start) == ActorMap->end()){
		cout << "Starting actor is not in the graph!!!" << endl;
		return year_DNE;
	}

	//ending actor is not found
	if (ActorMap->find(actor_end) == ActorMap->end()){
		cout << "Ending actor is not in the graph!!!" << endl;
		return year_DNE;
	}

	
	while (!pq_movie.empty()){
		Movie* movieNode = pq_movie.top();
		pq_movie.pop();
		//connect two consecutive nodes
		for(int i = 1; i < (int)movieNode->actorList->size();i++){
			u->connect((*(movieNode->actorList))[i-1],(*(movieNode->actorList))[i]); 
		}
		//if years of the two nodes are the same and pq of movie is not empty
		if(!pq_movie.empty() && movieNode->year == pq_movie.top()->year){
			continue;
		}
		//check if the two nodes have a path connecting each other 
		if(u->find(temp) == u->find(tempEnd)){
			delete u;
			return movieNode->year;
		}
	}
	delete u;	
	return connectedYear;
}

void ActorGraph::deleteAll(){
    for( auto itr= ActorMap->begin(); itr != ActorMap->end();itr++){
        for(int i=0;i<itr->second->edgeList->size();i++)
            delete itr->second->edgeList->at(i);
        delete itr->second->edgeList;
        delete itr->second->adjList;
        delete itr->second->movieList;
        delete itr->second;
    }
    for( auto itr= MovieMap->begin(); itr != MovieMap->end();itr++){
        delete itr->second->actorList;
        delete itr->second;
    }
    delete ActorMap;
    delete MovieMap;
}
