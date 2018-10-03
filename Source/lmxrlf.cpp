
#include <cstdlib>
#include <iostream>

#include "../Header/lmxrlf.hpp"

using std::cerr;
using std::endl;

int GLOBAL = 10;
int F = 1;
int LOCAL = 10;

//Returns an independent set from given set
vector<string> GraphColoring::Lmxrlf::get_independent(vector<string> set) {
	vector<string> delta;
	for(unsigned i=0; i<set.size(); i++) {
		delta.push_back(set[i]);
		for(unsigned j=0; j<graph[set[i]].size(); j++) {
			delta.push_back(graph[set[i]][j]);
		}
	}
	vector<string> ret;
	for(map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		if(coloring[(*i).first] == -1) {
			int flag = 0;
			for(unsigned j=0; j<delta.size(); j++) {
				if(delta[j] == (*i).first) { flag = 1; }
			}
			if(!flag) { ret.push_back((*i).first); }
		}
	}
	return ret;
}

//Creates an independent set from the graph
vector<string> GraphColoring::Lmxrlf::make_independent_set() {
	vector<string> set;
	vector<string> todo = get_independent(set);
	while(todo.size()) {
		set.push_back(todo[rand() % todo.size()]);
		todo = get_independent(set);
	}
	return set;
}

//Objective function for LMXRLF
int GraphColoring::Lmxrlf::objf(vector<string> set) {
	int sum = 0;
	for(unsigned i=0; i<set.size(); i++) {
		int non = graph[set[i]].size();
		non = non*non;
		int summation = 0;
		for(unsigned j=0; j<graph[set[i]].size(); j++) {
			int inner = graph[graph[set[i]][j]].size();
			summation += inner*inner*inner;
		}
		sum += summation*non;
	}
	return sum;
}

//Returns the value from the list of best solutions with the minimum objective function
int GraphColoring::Lmxrlf::min_objf(vector< vector<string> > list_of_best) {
	if(list_of_best.size() == 0) {
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int min = objf(list_of_best[0]);
	for (unsigned i=1; i<list_of_best.size(); i++) {
		int temp = objf(list_of_best[i]);
		if(temp < min) {
			min = temp;
		}
	}
	return min;
}

//Returns the value from the list of best solutions with the maximum objective function
int GraphColoring::Lmxrlf::max_objf(vector< vector<string> > list_of_best) {
	if(list_of_best.size() == 0) {
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int max = objf(list_of_best[0]);
	for(unsigned i=1; i<list_of_best.size(); i++) {
		int temp = objf(list_of_best[i]);
		if(temp > max) {
			max = temp;
		}
	}
	return max;
}

//Returns the index from the list of best solutions with the minimum objective function
int GraphColoring::Lmxrlf::min_pos_objf(vector< vector<string> > list_of_best) {
	if(list_of_best.size() == 0) {
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int min = objf(list_of_best[0]);
	int min_pos = 0;
	for(unsigned i=1; i<list_of_best.size(); i++) {
		int temp = objf(list_of_best[i]);
		if(temp < min) {
			min = temp;
			min_pos = i;
		}
	}
	return min_pos;
}

//Returns the index from the list of best solutions with the maximum objective function
int GraphColoring::Lmxrlf::max_pos_objf(vector< vector<string> > list_of_best) {
	if(list_of_best.size() == 0) {
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int max = objf(list_of_best[0]);
	int max_pos = 0;
	for (unsigned i=1; i<list_of_best.size(); i++) {
		int temp = objf(list_of_best[i]);
		if(temp > max) {
			max = temp;
			max_pos = i;
		}
	}
	return max_pos;
}

//Returns a set of uncolored neighbors from the input set
vector<string> GraphColoring::Lmxrlf::uncolored_neighbor(vector<string> new_set) {
	vector<string> delta;
	for(map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		int flag = 0;
		for(unsigned j=0; j<new_set.size(); j++) {
			if(new_set[j] == (*i).first) {
				flag = 1;
			}
		}
		if(!flag) {
			delta.push_back((*i).first);
		}
	}
	vector<string> out;
	for(map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		int initf = 1;
		for(unsigned j=0; j<delta.size(); j++) {
			if((*i).first == delta[j]) {
				initf = 0;
			}
		}
		if(!initf) {
			int count = 0;
			for(unsigned j=0; j<(*i).second.size(); j++) {
				for(unsigned y=0; y<delta.size(); y++) {
					if((*i).second[j] == delta[y]) {
						count += 1;
					}
				}
			}
			if(count == (int)(*i).second.size()) {
				out.push_back((*i).first);
			}
		}
	}
	return out;
}

map<string,int> GraphColoring::Lmxrlf::lmxrlf_alg(int endcond) {
	map< string, vector<string> > Graph_temp;
	vector< vector<string> > list_of_best_solutions;
	srand(time(NULL));
	int colored_nodes = 0;
	int Color = 0;
	for(map< string,int >::iterator i = coloring.begin(); i != coloring.end(); i++) {
		if((*i).second != -1) {
			colored_nodes += 1;
		}
		if((*i).second > Color) {
			Color = (*i).second;
		}
	}
	if(Color > 0) { Color += 1; }
	do {
		int global_iterations;
		if (Color == 0) { global_iterations = F*GLOBAL; }
		else { global_iterations = (int)(GLOBAL*(float)(1-(float)((colored_nodes*colored_nodes)/(graph.size()*graph.size())))); }
		vector<string> set = make_independent_set();
		list_of_best_solutions.push_back(set);
		for(int i=0; i<global_iterations; i++) {
			//Remove vertices from S until at least one does not have a colored neighbor
			vector<string> set_t = set;
			while(uncolored_neighbor(set_t).size() == 0) {
				int removal = rand() % set_t.size();
				set_t.erase(set_t.begin() + removal);
			}
			//Add randomly vertices which do not have colored neighbors to S
			vector<string> ucn = uncolored_neighbor(set_t);
			while(ucn.size() > 0) {
				set_t.push_back(ucn[rand() % ucn.size()]);
				ucn = uncolored_neighbor(set_t);
			}
			//Check ObjF of new set and add if larger than min
			if(objf(set_t) > min_objf(list_of_best_solutions)) {
				list_of_best_solutions.push_back(set_t);
				list_of_best_solutions.erase(list_of_best_solutions.begin() + min_pos_objf(list_of_best_solutions));
			}
		}
		for(unsigned i=0; i<list_of_best_solutions.size(); i++) {
			int flag = 0;
			vector<string> S_plus = list_of_best_solutions[i];
			for(int j=0; j<LOCAL; j++) {
				//remove random vertices from S_star
				vector<string> S_star = list_of_best_solutions[i];
				while(uncolored_neighbor(S_star).size() == 0) {
					S_star.erase(S_star.begin() + (rand() % S_star.size()));
				}
				//Add randomly vertices which do not have colored neighbors to S_star
				vector<string> ucn = uncolored_neighbor(S_star);
				while(ucn.size() > 0) {
					S_star.push_back(ucn[rand() % ucn.size()]);
					ucn = uncolored_neighbor(S_star);
				}
				//Check ObjF of S_star and add if smaller than original
				if(objf(S_star) > objf(S_plus)) {
					S_plus = S_star;
					flag = 1;//TODO: flag is never used?
				}
			}
			list_of_best_solutions[i] = S_plus;
		}
		//Color each vertex in the solution with the highest objf (making sure they haven't already been colored)
		vector<string> max_objf = list_of_best_solutions[max_pos_objf(list_of_best_solutions)];
		for(unsigned i=0; i<max_objf.size(); i++) {
			if(coloring[max_objf[i]] == -1) {
				coloring[max_objf[i]] = Color;
				colored_nodes += 1;
			}
		}
		//Remove all S from list of best solutions that have a common vertex with the best solution with maximum objf
		for(unsigned i=0; i<max_objf.size(); i++) {
			for(unsigned j=0; j<list_of_best_solutions.size(); j++) {
				int flag = 0;
				for(unsigned k=0; k<list_of_best_solutions[j].size(); k++) {
					if(max_objf[i] == list_of_best_solutions[j][k]) {
						flag = 1;
					}
				}
				if(flag) {
					list_of_best_solutions.erase(list_of_best_solutions.begin() + j);
					j--;
				}
			}
		}
		Color += 1;
	} while(colored_nodes < endcond-1);
	return coloring;
}

//Runs LMXRLF starting with a fully uncolored graph
map<string,int> GraphColoring::Lmxrlf::color() {
	if (this->condition == 0) { this->condition = graph.size(); }
	for(map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++) {
		coloring[(*i).first] = -1;
	}
	return lmxrlf_alg(this->condition);
}

