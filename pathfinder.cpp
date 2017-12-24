/*
 * ActorEdge.cpp
 * Author: <Haonan Huang> <Nang Chen>
 * Date:   <12/7/2017>
 *
 * This file is meant to exist as main.cpp file for pathFinder
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
using namespace std;

#define FIVE 5
#define FOUR 4
#define THREE 3
#define TWO 2
#define ONE 1
#define ZERO 0

int main(int argc, const char * argv[]) {
	//if number of arguments is incorrect
	if (argc != FIVE){
		cout<<"Incorrect number of arguments"<<endl;
		return 0;
	}

    //load the input file into the graph
	ActorGraph * tempgraph = new ActorGraph();
	tempgraph->loadFromFile(argv[ONE],false);
	ifstream infile;
	ofstream outfile;
	string nextString = " ";
	vector<string> startList;
	vector<string> endList;
	infile.open(argv[THREE]);
	getline(infile,nextString);
	string actor_start;
	string actor_end;
    
    //open the output file and write the header for the file
    outfile.open(argv[FOUR]);
    outfile << "(actor)--[movie#@year]-->(actor)--..." << endl;

	cout << "Reading from file: " << argv [THREE] << "..."<<endl;
	while(1){
		if(infile.is_open()){
			getline(infile,nextString);
			if (infile.eof() || !infile.good()){
				break;
			}
            if(nextString != ""){
                std::istringstream iss(nextString);
                std::string token;
                //separate the string by tab
                while(std::getline(iss, token, '\t'))
                startList.push_back(token);
                actor_start = startList.at(0);
                actor_end = startList.at(1);
                startList.pop_back();
                startList.pop_back();
            }
		}
		else{
			//tempgraph->deleteAll();
        		//delete(tempgraph);
			return 0;
		}

        //load the BFS method if the user indicate u
		if(strcmp(argv[TWO],"u") == 0){
			tempgraph -> find_BFS(actor_start,actor_end);
		}
        //load the Dijkstra method if the user indicate w
		else if(strcmp(argv[TWO],"w") == 0){
			tempgraph -> find_Dijkstra(actor_start,actor_end);
		}
        //outfile the error message
		else{
			cout << "Invalid input, u for unweighted and w for weighted." << endl;
			//tempgraph->deleteAll();
        		//delete(tempgraph);
			return 0;
		}
        //print path
        if(outfile.is_open()){
            outfile <<"("<< actor_start<<")--";
            tempgraph -> printPath(actor_start,actor_end,outfile);
        }
        
	}
	tempgraph->deleteAll();
	delete(tempgraph);
	infile.close();
	outfile.close();
	return 0;

}
