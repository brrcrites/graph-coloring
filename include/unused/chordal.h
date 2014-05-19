#include <vector>
#include <map>
#include <string>
#include <stack>
#include <deque>

#ifndef _GUARD_
#define _GUARD_
#include "graph_print.h"
#endif

stack<string> mcs(map< string, vector<string> > Graph)
{
	map< string, int > Weight;
	stack<string> Ordering;
	int size = 0;
	for(map< string, vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		size += 1;
		Weight[(*i).first] = 0;
	}
	for(int i = 0; i < size; i++)
	{
		int max_weight = -1;
		string max_vertex = "error";
		for(map< string, vector<string> >:: iterator j = Graph.begin(); j != Graph.end(); j++)
		{
			if(Weight[(*j).first] > max_weight)
				max_vertex = (*j).first;
		}
		Ordering.push(max_vertex);
		for(int j = 0; j<Graph[max_vertex].size(); j++)
		{
			Weight[Graph[max_vertex][j]] += 1;
		}
		Graph.erase(max_vertex);
	}
	return Ordering;
}

map< string,int > chordal(map< string, vector<string> > Graph)
{
	stack<string> Todo = mcs(Graph);
	map< string, int > Colors;
	
	while(!Todo.empty())
	{
		string min = Todo.top();
	
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
		Todo.pop();
	}	
	
	return Colors;
}
