##Graph Coloring library 

Please note, currently the only algorithm that has been verified to work correctly is DSATUR. The other algorithms seem to have been broken during a recent rewrite.

(Nodes are represented as strings)

    map<string,vector<string> >
A map of the node, to the list of nodes connected to it

    Graph()
Creates a new graph with no nodes/edges and uses default DSATUR coloring algorithm
    
    add_node(string new_node)
Creates a node <new_node> in the graph with no edges
    
    add_edge(string source,string sink)
Adds sink to the list of nodes connected to source. Adds source to the list of nodes connected to sink. If either source or sink don't exist in the graph, they will be added.
    
    color(int condition)
Colors the graph using condition as a stopping condition (for specific algorithms). Returns a map of nodes, to their colors (map<string,int>)

    verify()
verifies coloring of the graph

##Available Algorithms: 
(See reference papers for descriptions)

    set_algorithm(new_algorithm)

- DSATUR (New Methods to Color the Vertices of a Graph - Brelaz et al.): kDSATUR
- Chordal (Register Allocation via Coloring of Chordal Graphs - Magno et al.): kChordal
- lmXRLF (Efficient Coloring of a Large Spectrum of Graphs - Kirovski et al.): kLMXRLF
- Hybrid Tabu (Custom, based on Efficient Coloring... - Kirovski et al.): kHybrid
- Hybrid DSATUR (Custom, based on Efficient Coloring... - Kirovski et al.): kHybridDSATUR

(Below is implemented but not Accessable via main)

- [k-coloring] TabuCol (Using Tabu Search Techniques for Graph Coloring - Hertz et al.): tabucol

##Running Tests/Test Sets:
You can test that the program is running correctly by running the following command, which will build a graph for the wheel test, run the DSATUR coloring algorithm, then print the chromatic number.

    make test

You can run specific sets of tests with each graph coloring algorithm by specifying which test set test to run by editing the TEST make variable (by default the main will run the test/test set with DSATUR).

    make test TEST="group_name"

Where "group_name" is the name of a test group from this list:

- all (runs every test)
- fullins
- insertions
- anna
- ash
- david
- dsjc
- dsjr
- flat
- fpsol
- games
- homer
- huck
- inithx
- jean
- le
- miles
- mug
- mulsol
- myciel
- queen
- r125
- r250
- r1000
- rtotal
- school
- will
- zeroin
- bondymurty
- chvatal
- cube
- dodeca
- grotzsch
- grunbaum
- icosa
- kuratowski
- india
- mycielski
- octa
- petersen
- ramsey
- tetra
- wheel

##Adding Tests:

You can also add tests to the test_cases folder that are in the following formats:

Edge List Input File Format:

    c FILE: <filename.col>
    c SOURCE: <source>
    c DESCRIPTION: <description>

    p edge <|#nodes|> <|#edges|>
    e <source> <sink>

Edge Matrix Input File Format:

    <|#nodes|>
    <|#nodes|x|#nodes| matrix>

    1 indicates an edge between column node and row node
    0 indicates a lack of an edge

Once you have added tests, you can give them a group handle in the test_cases.mk file, and then register them in the if/else tree under the "test" command.

##Visualizer output:

    write_graph(string graph_name)

Will write a .dot file named graph_name.dot
If no argument is provided, writes to colored_graph.dot. The .dot file has
    nodes colored appropriately and with the second line showing the color id
    in case the colors are too close.

Example usage: (Without text file input)

    //Create the graph
    Graph new_graph();
    //Add all of the nodes/edges
    string node1 = "node1";
    string node2 = "node2";
    new_graph.add_node(node1);
    new_graph.add_node(node2);
    new_graph.add_edge(node1,node2);
    ...
    //Color the graph
    map<int,string> coloring = new_graph.color();
