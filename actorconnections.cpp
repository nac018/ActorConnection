/*
 *  ActorConnections.cpp
 *  Author: <Haonan Huang> <Nang Chen>
 *  Date:   <12/7/2017>
 *  
 *  This file is meant to exist as main.cpp file for actorconnections
 */
#include "ActorGraph.h"
#include "ActorNode.h"
#include "ActorEdge.h"
#include "Movie.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

#define FIVE 5
#define FOUR 4
#define THREE 3
#define TWO 2
#define ONE 1
#define ZERO 0

int main(int argc, const char * argv[]) {
	if (argc != FOUR && argc != FIVE){
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}
    	//load the input file into a graph	
	ActorGraph tempgraph;
	tempgraph.simpleLoad(argv[ONE],false);
	ifstream infile;
	ofstream outfile;
	string nextString;
	infile.open(argv[TWO]);
	getline(infile,nextString);
	string actor_start;
	string actor_end;
	//open the output file and write the header for the file
	outfile.open(argv[THREE]);
	outfile<<"Actor1\tActor2\tYear"<<endl;

	cout << "Reading from file: " << argv [TWO] << "..."<<endl;

	int connectedYear;

	while(1){
		//separate the string by tab
		if(infile.is_open()){
			getline(infile,nextString);
			if(infile.eof() || !infile.good()){
				break;
			}
			istringstream iss(nextString);
			getline(iss,actor_start,'\t');
			getline(iss,actor_end,'\t');
		}
		else{
			return 0;
		}
		//load the BFS method if the user indicate bfs
		if(strcmp(argv[FOUR],"bfs") == 0){
			connectedYear = tempgraph.connect_bfs(actor_start,actor_end);
		}
		//load the disjoint set method if the user indicate ufind
		else if(strcmp(argv[FOUR],"ufind") == 0){
			connectedYear = tempgraph.connect_ufind(actor_start,actor_end);
		}
		else if(argc == 4){
			connectedYear = tempgraph.connect_ufind(actor_start,actor_end);
		}
		else{
			cout << "Invalid input, bfs for BFS and ufind for Union Find." << endl;
			return 0;
		}
		 //print the year
		outfile << actor_start << "\t" << actor_end << "\t" << connectedYear << endl;
	}
	tempgraph.deleteAll();
	infile.close();
	outfile.close();
	return 0;
}
