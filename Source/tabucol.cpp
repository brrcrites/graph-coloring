
#include "../Header/tabucol.h"

#include <queue>
#include <cstdlib>
#include <iostream>

using std::queue;
using std::cerr;
using std::endl;

const int TABU_SIZE = 25;
const int REP = 100;
const int NBMAX = 1000;

int GraphColoring::tabucol::f(map<string,int> coloring) {
	int sum = 0;
	for(map< string,vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		for(unsigned j=0; j< i->second.size(); j++) {
			if(coloring[i->first] == coloring[i->second[j]]) {
				sum += 1;
			}
		}
	}
	return sum;
}

map<string,int> GraphColoring::tabucol::color(int k) {
	srand(time(NULL));
	for(map< string,vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		coloring[(*i).first] = rand() % k;
	}
	queue<int> tabu_color;
	queue<string> tabu_vertex;
	for(int i=0; i<TABU_SIZE; i++) {
		map< string,vector<string> >::iterator x = graph.begin();
		std::advance(x,(rand() % graph.size()));
		tabu_vertex.push((*x).first);
		tabu_color.push(rand() % k);
	}
	int nbiter = 0;
	while(f(coloring) > 0 && nbiter < NBMAX) {
		int best_color = -1;
		string best_vertex;
		int x = 0;
		int original_f = f(coloring);
		while(x < REP) {
			int flag = 0;
			int move_color;
			string move_vertex;
			while(!flag) {
				move_color = rand() % k;
				map< string,vector<string> >::iterator mv = graph.begin();
				std::advance(mv,(rand() % graph.size()));
				move_vertex = (*mv).first;
				int inner_flag = 0;
				for(unsigned i=0; i<tabu_vertex.size(); i++) {
					const string& temp_vertex = tabu_vertex.front();
					int temp_color = tabu_color.front();
					if(temp_vertex == move_vertex && temp_color == move_color) {
						flag = 1;
					}
					tabu_vertex.pop();
					tabu_color.pop();
					tabu_vertex.push(temp_vertex);
					tabu_color.push(temp_color);
				}
				if(!inner_flag) {
					flag = 1;
				}
			}
			if(best_color == -1) {
				best_color = move_color;
				best_vertex = move_vertex;
			}
			map< string,int > Colors_move = coloring;
			Colors_move[move_vertex] = move_color;
			map< string,int > Colors_best = coloring;
			Colors_best[best_vertex] = best_color;
			if(f(Colors_move) < f(Colors_best)) {
				best_vertex = move_vertex;
				best_color = move_color;
			}
			x += 1;
			if(f(Colors_move) < original_f) {
				x = REP;
			}
		}
		if(best_color == -1) {
			map< string, int > ret;
			cerr << "Best Color was never updated in the loop" << endl;
			coloring = ret;
			return coloring;
		}
		tabu_color.pop();
		tabu_color.push(best_color);
		tabu_vertex.pop();
		tabu_vertex.push(best_vertex);
		coloring[best_vertex] = best_color;
		nbiter += 1;
	}

	if(!verify()) {
		map< string,int > ret;
		coloring = ret;
	}
	return coloring;
}

