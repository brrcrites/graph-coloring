#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

//Function for splitting strings into their words on whitespace
vector<string> split(string s)
{
	vector<string> ret;
	int end;
	while(s.rfind("1") != s.size()-1 || s.rfind("0") != s.size()-1 || 
			s.rfind("X") != s.size()-1 || s.rfind("x") != s.size()-1) {
		s = s.substr(0,s.size()-1);
	}
	while((end = s.find(" ")) < s.length())
	{
		ret.push_back(s.substr(0,end));
		s = s.substr(end+1);
	}
	ret.push_back(s);
	return ret;
}

map< string, vector<string> > parse_edge_list(char* input_file)
{
	map< string, vector<string> > Graph;
	
	ifstream file(input_file);
	if(file.is_open())
	{
		string line;
		int vertices = -1;
		int flag = 0;
		while(!flag && getline(file,line))
		{
			while(line.size() == 0)
				getline(file,line);
			vector<string> words = split(line);
			if(words.size() != 0)
			{
				if(words[0] == "p")
				{
					vertices = atoi(words[2].c_str());
					flag = 1;
				}
			}
		}
		if(!flag || vertices == -3)
		{
			cerr << "File is missing parameter line before edge list" << endl;
			cerr << "Should be: \"p edge <number of vertices> <number of edges>\"" << endl;
			return Graph;
		}
		for(int i=0; i<vertices; i++)
		{
			string pre = "v";
			string temp;
			ostringstream convert;
			convert << (i+1);
			temp = convert.str();
			pre.append(temp);
			vector<string> base;
			Graph[pre] = base;
		}
		while(getline(file,line))
		{
			vector<string> words = split(line);
			if(words[0] == "e")
			{
				string arg1 = "v";
				arg1.append(words[1]);
				string arg2 = "v";
				arg2.append(words[2]);
				vector<string> base;
				vector<string> base2;
				base = Graph[arg1];
				base2 = Graph[arg2];
				base.push_back(arg2);
				base2.push_back(arg1);
				Graph[arg1] = base;
				Graph[arg2] = base2;
			}
		}
	}
	else
	{
		cerr << "Input File Not Found" << endl;
		return Graph;
	}
	return Graph;
}

//Used to parse test inputs where the first line is the number of
//vertices, and the next lines are the edge matrix
map< string, vector<string> > parse_edge_matrix(char* input_file)
{
	map< string, vector<string> > Graph;
	string pre = "v";

	ifstream file(input_file);
	if(file.is_open())
	{
		string line;
		getline(file,line);
		vector<string> num = split(line);
		if(num.size() > 1)
		{
			cerr << line << endl;
			cerr << "No matrix size at top of file" << endl;
			return Graph;
		}
		int n = atoi(num[0].c_str());
		int i = 0;
		while(getline(file,line))
		{
			i += 1;
			vector<string> words = split(line);
			if(words.size() != n)
			{
				cerr << "Invalid Input, line " << i << " is not the correct length: " << line << endl;
				Graph.clear();
				return Graph;
			}
			vector<string> edges;
			for(int j = 0; j < n; j++)
			{
				if(words[j] == "1")
				{
					pre = "v";
					string temp;
					ostringstream convert;
					convert << (j+1);
					temp = convert.str();
					edges.push_back(pre.append(temp));
				}
			}
			pre = "v";
			string temp;
			ostringstream convert;
			convert << i;
			temp = convert.str();
			Graph[pre.append(temp)] = edges;
		}
		if(i != n)
		{
			cerr << "Input is not the right length" << endl;
			Graph.clear();
			return Graph;
		}
		file.close();
	}
	else
	{
		cerr << "Input File Not Found" << endl;
		return Graph;
	}
	return Graph;
}

//function for reading the input and creating a vector of vectors
//where the first index returns a vector of strings equivalent to
//all words on a line and the second index returns a word in that
//line, also does the majority of error handling for bad inputs
vector< vector<string> > get_input(char* input_file)
{
	vector< vector<string> > Input;

	ifstream file(input_file);
	if(file.is_open())
	{
		string line;
		while(getline(file,line))
		{
			vector<string> words = split(line);
			if(words.size() > 1)
			{
				for(int i=1; i<words.size(); i++)
				{
					if(words[i] != "0" && words[i] != "1" && words[i] != "x" && words[i] != "X")
					{
						cerr << "Problem with this Input Line: " << line << endl;
						cerr << "Problem is with word: \"" << words[i] << "\" at position " << i << endl;
						Input.clear();
						return Input;
					}
				}
			}
			else
			{
				cerr << "No Actuation Data Found, Please Check Input File" << endl;
				Input.clear();
				return Input;
			}
			Input.push_back(words);
		}
		file.close();
	}
	else
	{
		cerr << "Input File Not Found" << endl;
	}
	return Input;
}

//Builds the Edge List from a parsed input file and returns it as a map
//which takes in a node name and returns a vector of its neighbors
//assumes the graph is undirected
map< string, vector<string> > build_graph(vector< vector<string> > Input)
{
	map< string, vector<string> > Graph;
	for(int i=0; i<Input.size(); i++)
	{
		vector<string> edges;
		Graph[Input[i][0]] = edges;
	}
	for(int i=0; i<Input.size(); i++)
	{
		for(int j=i+1; j<Input.size(); j++)
		{
			for(int x=1; x<Input[i].size(); x++)
			{
				if(Input[i][x] != Input[j][x])
				{
					if(!(Input[j][x] == "x" || Input[j][x] == "X" || Input[i][x] == "x" || Input[i][x] == "X"))
					{
						vector<string> edgesi = Graph[Input[i][0]];
						vector<string> edgesj = Graph[Input[j][0]];
						int add = 1;
						for(int l=0; l<edgesi.size(); l++)
						{
							if(edgesi[l] == Input[j][0])
								add = 0;
						}
						if(add == 1)
						{
							edgesi.push_back(Input[j][0]);
							edgesj.push_back(Input[i][0]);
						}
						Graph[Input[i][0]] = edgesi;
						Graph[Input[j][0]] = edgesj;
					}
				}
			}
		}
	}
	return Graph;
}


