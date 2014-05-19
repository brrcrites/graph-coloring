#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <deque>
#include <ctime>

#ifndef _GUARD_
#define _GUARD_
#include "graph_print.h"
#endif

map< string,int > smallest_stack(map< string, vector<string> > Graph)
{
	map< string, int > Colors;
	map< string, int > Degree;
	stack<string> Smallest;
	for(map< string, vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		Degree[(*i).first] = (*i).second.size();
	}
	while(!Degree.empty())
	{
		string min = "error";
		int degree = -1;
		//Find the vertex with minimal degree
		for(map< string, int >::iterator i = Degree.begin(); i != Degree.end(); i++)
		{
			if(degree == -1)
			{
				degree = (*i).second;
				min = (*i).first;
			}
			if((*i).second < degree)
			{
				degree = (*i).second;
				min = (*i).first;
			}
		}
		Smallest.push(min);
		Degree.erase(min);
	}
	
	while(!Smallest.empty())
	{
		string min = Smallest.top();
	
		//find the minimum coloring number from the neighbors
		int color = 0;
		int done = 0;
		while(!done)
		{
			done = 1;
			for(int i=0; i<Graph[min].size(); i++)
			{
				if(Colors[Graph[min][i]] == color)
				{
					color += 1;
					done = 0;
				}
			}
		}
		//color with lowest color and remove the minimum from the todo list
		Colors[min] = color;
		Smallest.pop();
	}
	
	return Colors;
}
