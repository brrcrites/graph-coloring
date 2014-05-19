#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#ifndef _GUARD_
#define _GUARD_
#include "graph_print.h"
#endif

int GLOBAL = 10;
int F = 1;
int LOCAL = 10;

//Returns an independent set from given set
vector<string> get_independent(map< string,int > Colors, map< string, vector<string> > Graph, vector<string> set)
{
	vector<string> delta;
	for(int i=0; i<set.size(); i++)
	{
		delta.push_back(set[i]);
		for(int j=0; j<Graph[set[i]].size(); j++)
		{
			delta.push_back(Graph[set[i]][j]);
		}
	}
	vector<string> ret;
	for(map< string, vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		if(Colors[(*i).first] == -1)
		{
			int flag = 0;
			for(int j=0; j<delta.size(); j++)
			{
				if(delta[j] == (*i).first)
					flag = 1;
			}
			if(!flag)
				ret.push_back((*i).first);
		}
	}
	return ret;
}

//Creates an independent set from the graph
vector<string> make_independent_set(map< string,int > Colors, map< string, vector<string> > Graph)
{
	vector<string> set;
	vector<string> todo = get_independent(Colors,Graph,set);
	while(todo.size())
	{
		set.push_back(todo[rand() % todo.size()]);
		todo = get_independent(Colors,Graph,set);
	}
	return set;
}

//Objective function for LMXRLF
int objf(map< string, vector<string> > Graph, vector<string> set)
{
	int sum = 0;
	for(int i=0; i<set.size(); i++)
	{
		int non = Graph[set[i]].size();
		non = non*non;
		int summation = 0;
		for(int j=0; j<Graph[set[i]].size(); j++)
		{
			int inner = Graph[Graph[set[i]][j]].size();
			summation += inner*inner*inner;
		}
		sum += summation*non;
	}
	return sum;
}

//Returns the value from the list of best solutions with the minimum objective function
int min_objf(map< string, vector<string> > Graph, vector< vector<string> > list_of_best)
{
	if(list_of_best.size() == 0)
	{
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int min = objf(Graph,list_of_best[0]);
	for(int i=1; i<list_of_best.size(); i++)
	{
		int temp = objf(Graph,list_of_best[i]);
		if(temp < min)
		{
			min = temp;
		}
	}
	return min;
}

//Returns the value from the list of best solutions with the maximum objective function
int max_objf(map< string, vector<string> > Graph, vector< vector<string> > list_of_best)
{
	if(list_of_best.size() == 0)
	{
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int max = objf(Graph,list_of_best[0]);
	for(int i=1; i<list_of_best.size(); i++)
	{
		int temp = objf(Graph,list_of_best[i]);
		if(temp > max)
		{
			max = temp;
		}
	}
	return max;
}

//Returns the index from the list of best solutions with the minimum objective function
int min_pos_objf(map< string, vector<string> > Graph, vector< vector<string> > list_of_best)
{
	if(list_of_best.size() == 0)
	{
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int min = objf(Graph,list_of_best[0]);
	int min_pos = 0;
	for(int i=1; i<list_of_best.size(); i++)
	{
		int temp = objf(Graph,list_of_best[i]);
		if(temp < min)
		{
			min = temp;
			min_pos = i;
		}
	}
	return min_pos;
}

//Returns the index from the list of best solutions with the maximum objective function
int max_pos_objf(map< string, vector<string> > Graph, vector< vector<string> > list_of_best)
{
	if(list_of_best.size() == 0)
	{
		cerr << "List of Best Solutions is of size 0" << endl;
		return -1;
	}
	int max = objf(Graph,list_of_best[0]);
	int max_pos = 0;
	for(int i=1; i<list_of_best.size(); i++)
	{
		int temp = objf(Graph,list_of_best[i]);
		if(temp > max)
		{
			max = temp;
			max_pos = i;
		}
	}
	return max_pos;
}

//Returns a set of uncolored neighbors from the input set
vector<string> uncolored_neighbor(map< string, vector<string> > Graph, map< string, int > Colors, vector<string> new_set)
{
	vector<string> delta;
	for(map< string, vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		int flag = 0;
		for(int j=0; j<new_set.size(); j++)
		{
			if(new_set[j] == (*i).first)
			{
				flag = 1;
			}
		}
		if(!flag)
		{
			delta.push_back((*i).first);
		}
	}
	vector<string> out;
	for(map< string, vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		int initf = 1;
		for(int j=0; j<delta.size(); j++)
		{
			if((*i).first == delta[j])
			{
				initf = 0;
			}
		}
		if(!initf) {
			int count = 0;
			for(int j=0; j<(*i).second.size(); j++)
			{
				for(int y=0; y<delta.size(); y++)
				{
					if((*i).second[j] == delta[y])
					{
						count += 1;
					}
				}
			}
			if(count == (*i).second.size())
			{
				out.push_back((*i).first);
			}
		}
	}
	return out;
}

map< string,int > lmxrlf(map< string, vector<string> > Graph, map< string,int > Colors, int endcond)
{
	map< string, vector<string> > Graph_temp;
	vector< vector<string> > list_of_best_solutions;
	srand(time(NULL));
	int colored_nodes = 0;
	int Color = 0;
	for(map< string,int >::iterator i = Colors.begin(); i != Colors.end(); i++)
	{
		if((*i).second != -1)
		{
			colored_nodes += 1;
		}
		if((*i).second > Color)
		{
			Color = (*i).second;
		}
	}
	if(Color > 0)
		Color += 1;
	do {
		int global_iterations;
		if(Color == 0) global_iterations = F*GLOBAL;
		else global_iterations = (int)(GLOBAL*(float)(1-(float)((colored_nodes*colored_nodes)/(Graph.size()*Graph.size()))));
		vector<string> set = make_independent_set(Colors,Graph);
		list_of_best_solutions.push_back(set);
		for(int i=0; i<global_iterations; i++)
		{
			//Remove vertices from S until at least one does not havea colored neighbor
			vector<string> set_t = set;
			while(uncolored_neighbor(Graph, Colors, set_t).size() == 0)
			{
				int removal = rand() % set_t.size();
				set_t.erase(set_t.begin() + removal);
			}
			//Add randomly vertices which do not have colored neighbors to S
			vector<string> ucn = uncolored_neighbor(Graph, Colors, set_t);
			while(ucn.size() > 0)
			{
				set_t.push_back(ucn[rand() % ucn.size()]);
				ucn = uncolored_neighbor(Graph, Colors, set_t);
			}
			//Check ObjF of new set and add if larger than min
			if(objf(Graph, set_t) > min_objf(Graph, list_of_best_solutions))
			{
				list_of_best_solutions.push_back(set_t);
				list_of_best_solutions.erase(list_of_best_solutions.begin() + min_pos_objf(Graph, list_of_best_solutions));
			}
		}
		for(int i=0; i<list_of_best_solutions.size(); i++)
		{
			int flag = 0;
			vector<string> S_plus = list_of_best_solutions[i];
			for(int j=0; j<LOCAL; j++)
			{
				//remove random vertices from S_star
				vector<string> S_star = list_of_best_solutions[i];
				while(uncolored_neighbor(Graph, Colors, S_star).size() == 0)
				{
					S_star.erase(S_star.begin() + (rand() % S_star.size()));
				}
				//Add randomly vertices which do not have colored neighbors to S_star
				vector<string> ucn = uncolored_neighbor(Graph, Colors, S_star);
				while(ucn.size() > 0)
				{
					S_star.push_back(ucn[rand() % ucn.size()]);
					ucn = uncolored_neighbor(Graph, Colors, S_star);
				}
				//Check ObjF of S_star and add if smaller than original
				if(objf(Graph, S_star) > objf(Graph, S_plus))
				{
					S_plus = S_star;
					flag = 1;
				}
			}
			list_of_best_solutions[i] = S_plus;
		}
		//Color each vertex in the solution with the highest objf (making sure they haven't already been colored)
		vector<string> max_objf = list_of_best_solutions[max_pos_objf(Graph,list_of_best_solutions)];
		for(int i=0; i<max_objf.size(); i++)
		{
			if(Colors[max_objf[i]] == -1)
			{
				Colors[max_objf[i]] = Color;
				colored_nodes += 1;
			}
		}
		//Remove all S from list of best solutions that have a common vertex with the best solution with maximum objf
		for(int i=0; i<max_objf.size(); i++)
		{
			for(int j=0; j<list_of_best_solutions.size(); j++)
			{
				int flag = 0;
				for(int k=0; k<list_of_best_solutions[j].size(); k++)
				{
					if(max_objf[i] == list_of_best_solutions[j][k])
					{
						flag = 1;
					}
				}
				if(flag)
				{
					list_of_best_solutions.erase(list_of_best_solutions.begin() + j);
					j--;
				}
			}
		}
		Color += 1;
	} while(colored_nodes < endcond);
	
	return Colors;
}

//Runs LMXRLF starting with a fully uncolored graph
map< string,int > lmxrlf_base(map< string,vector<string> > Graph, int endcond)
{
	map< string,int > Colors;
	for(map< string, vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		Colors[(*i).first] = -1;
	}
	return lmxrlf(Graph,Colors,endcond);
}

