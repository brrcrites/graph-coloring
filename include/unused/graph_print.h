#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>

//Used to print the Chromatic Color as well as the runtime
void print_fullstats(map< string,int > Colors, clock_t start, clock_t end, string algorithm)
{
	int largest = 0;
	for(map< string, int >::iterator i = Colors.begin(); i != Colors.end(); i++)
	{	
		if((*i).second > largest) largest = (*i).second;
	}

	cout << algorithm << " Chromatic Number: " << largest+1 << endl;
	cout << algorithm << " Runtime: " << (double)((double)(end-start) / (double)(CLOCKS_PER_SEC))*1000000 << " microseconds" << endl;
}

//Used to print the Chromatic Color
void print_notime(map< string,int > Colors, string algorithm)
{
	int largest = 0;
	for(map< string, int >::iterator i = Colors.begin(); i != Colors.end(); i++)
	{	
		if((*i).second > largest) largest = (*i).second;
	}

	cout << algorithm << " Chromatic Number: " << largest+1 << endl;
}

//Used to print the color of each node in the graph
void print_coloring(map< string,int > Colors, string algorithm)
{
	cout << "----------" << algorithm << " Colorings----------" << endl;
	for(map< string,int >::iterator i = Colors.begin(); i != Colors.end(); i++)
	{
		cout << (*i).first << " " << (*i).second << endl;
	}
}

//Used to test if the graph has a valid coloring
bool verify(map< string,vector<string> > Graph, map< string,int > Colors)
{
	for(map< string,vector<string> >::iterator i = Graph.begin(); i != Graph.end(); i++)
	{
		for(int j=0; j<(*i).second.size(); j++)
		{
			if(Colors[(*i).first] == Colors[(*i).second[j]])
			{
				return false;
			}
		}
	}
	return true;
}
