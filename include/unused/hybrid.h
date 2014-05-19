#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#ifndef _LMXRLF_GUARD_
#define _LMXRLF_GUARD_
#include "lmxrlf.h"
#endif

#ifndef _GUARD_
#define _GUARD_
#include "graph_print.h"
#endif

#ifndef _TABU_GUARD_
#define _TABU_GUARD_
#include "tabucol.h"
#endif

map< string,vector<string> > get_subgraph(map< string,vector<string> > Graph, map< string,int > Colors)
{
	map< string,vector<string> > subgraph;
	for(map< string,vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		if(Colors[(*i).first] == -1)
		{
			vector<string> neighbors;
			for(int j=0; j<(*i).second.size(); j++)
			{
				if(Colors[(*i).second[j]] == -1)
					neighbors.push_back((*i).second[j]);
			}
			subgraph[(*i).first] = neighbors;
		}
	}
	return subgraph;
}

map< string,int > hybrid(map< string, vector<string> > Graph, int CARR)
{
	map< string,int > Colors = lmxrlf_base(Graph,CARR);
	
	//*********************************
	//***** Find the Sub Coloring *****
	//*********************************
	int Color_temp = 0;
	for(map< string,int >::iterator i = Colors.begin(); i != Colors.end(); i++)
	{
		if((*i).second > Color_temp)
		{
			Color_temp = (*i).second;
		}
	}
	Color_temp += 1;
	
	map< string,int > Colors_temp = Colors;
	
	Colors = lmxrlf(Graph,Colors,Graph.size());
	int Color = 0;
	for(map< string,int >::iterator i = Colors.begin(); i != Colors.end(); i++)
	{
		if((*i).second > Color)
		{
			Color = (*i).second;
		}
	}
	
	//******************************************************
	//***** Run Remaineder through Tabucol and Recolor *****
	//******************************************************
	int subset_color = Color;
	
	map< string,vector<string> > Graph_subset = get_subgraph(Graph,Colors_temp);
	map< string,int > tabu_color = tabucol(Graph_subset,subset_color);
	map< string,int > best;
	while(tabu_color.size() > 0)
	{
		best = tabu_color;
		subset_color -= 1;
		tabu_color = tabucol(Graph_subset,subset_color);
	}
	if(best.size() > 0)
	{
		for(map< string,int >::iterator i = best.begin(); i != best.end(); i++)
		{
			Colors[(*i).first] = Color_temp + (*i).second;
		}
	}

	return Colors;
}

//Starts by using DSATUR to get an approximate coloring and then uses decrementing
//tabucol runs to try and reduce the chromatic number
map< string,int > hybrid_dsatur(map< string,vector<string> > Graph)
{
	map< string,int > Colors = dsatur(Graph);

	int largest = 0;
	for(map< string, int >::iterator i = Colors.begin(); i != Colors.end(); i++)
	{	
		if((*i).second > largest) largest = (*i).second;
	}
	largest += 1;

	map< string,int > tabu_color = tabucol(Graph,largest);
	map< string,int > best = Colors;
	while(tabu_color.size() > 0)
	{
		best = tabu_color;
		largest -= 1;
		tabu_color = tabucol(Graph,largest);
	}

	return best;
}