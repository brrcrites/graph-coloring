#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <math.h>
#include <queue>

#ifndef _GUARD_
#define _GUARD_
#include "graph_print.h"
#endif

int TABU_SIZE = 25;
int REP = 100;
int NBMAX = 1000;

int f(map< string,vector<string> > Graph, map< string,int > Colors)
{
	int sum = 0;
	for(map< string,vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		for(int j=0; j< i->second.size(); j++)
		{
			if(Colors[i->first] == Colors[i->second[j]])
			{
				sum += 1;
			}
		}
	}
	return sum;
}

map< string,int > tabucol(map< string,vector<string> > Graph, int k)
{
	map< string,int > Colors;
	srand(time(NULL));
	for(map< string,vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		Colors[(*i).first] = rand() % k;
	}
	queue<int> tabu_color;
	queue<string> tabu_vertex;
	for(int i=0; i<TABU_SIZE; i++)
	{
		map< string,vector<string> >::iterator x = Graph.begin();
		std::advance(x,(rand() % Graph.size()));
		tabu_vertex.push((*x).first);
		tabu_color.push(rand() % k);
	}
	int nbiter = 0;
	while(f(Graph,Colors) > 0 && nbiter < NBMAX)
	{
		int best_color = -1;
		string best_vertex;
		int x = 0;
		int original_f = f(Graph,Colors);
		while(x < REP)
		{
			int flag = 0;
			int move_color;
			string move_vertex;
			while(!flag)
			{
				move_color = rand() % k;
				map< string,vector<string> >::iterator mv = Graph.begin();
				std::advance(mv,(rand() % Graph.size()));
				move_vertex = (*mv).first;
				int inner_flag = 0;
				for(int i=0; i<tabu_vertex.size(); i++)
				{
					const string& temp_vertex = tabu_vertex.front();
					int temp_color = tabu_color.front();
					if(temp_vertex == move_vertex && temp_color == move_color)
					{
						flag = 1;
					}
					tabu_vertex.pop();
					tabu_color.pop();
					tabu_vertex.push(temp_vertex);
					tabu_color.push(temp_color);
				}
				if(!inner_flag)
				{
					flag = 1;
				}
			}
			if(best_color == -1)
			{
				best_color = move_color;
				best_vertex = move_vertex;
			}
			map< string,int > Colors_move = Colors;
			Colors_move[move_vertex] = move_color;
			map< string,int > Colors_best = Colors;
			Colors_best[best_vertex] = best_color;
			if(f(Graph,Colors_move) < f(Graph,Colors_best))
			{
				best_vertex = move_vertex;
				best_color = move_color;
			}
			x += 1;
			if(f(Graph,Colors_move) < original_f)
			{
				x = REP;
			}
		}
		if(best_color == -1)
		{
			map< string, int > ret;
			cerr << "Best Color was never updated in the loop" << endl;
			Colors = ret;
			return Colors;
		}
		tabu_color.pop();
		tabu_color.push(best_color);
		tabu_vertex.pop();
		tabu_vertex.push(best_vertex);
		Colors[best_vertex] = best_color;
		nbiter += 1;
	}

	if(!verify(Graph,Colors))
	{
		map< string,int > ret;
		Colors = ret;
	}
	
	return Colors;
}

