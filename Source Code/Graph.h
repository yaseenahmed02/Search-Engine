//
// Created by Yaseen Ahmed on 2022-04-27.
//

#ifndef SEARCHENGINEPROJECT_GRAPH_H
#define SEARCHENGINEPROJECT_GRAPH_H

#include <vector>
#include <iostream>
using namespace std;

class Graph {

private:
    vector<vector<int>> adj;//adj list
    vector<bool> visited;
    int V; //num of verticies
public:

    Graph(int); //constructor
    void add_edge(int, int);
    void dfs(int v);
    void display();
    int num_edges_out(int v);
    int num_edges_in(int v);
    int get_num_nodes();
    Graph get_transpose();
    vector<int> get_nodes_pointing_to_v(int);
    void displayGraph();
};


#endif //SEARCHENGINEPROJECT_GRAPH_H
