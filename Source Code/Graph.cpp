//
// Created by Yaseen Ahmed on 2022-04-27.
//

#include "Graph.h"

Graph::Graph(int vertex_count) {
    this -> V = vertex_count;
    adj.resize(V);
    visited.resize(V);
    fill(visited.begin(), visited.end(), 0);
}



//add edge
void Graph::add_edge(int src, int dest) {
    adj[src].push_back(dest);
}


//depth first search
void Graph::dfs(int v) {
    if(!visited[v]) return;
    visited[v] = true;
    for(int i=0; i<adj[v].size(); i++) {
        int neighbor = adj[v][i];
        dfs(neighbor);
    }
}


//displays the content of a graph
void Graph::display() {
    for(int i = 0; i<V; i++) {
        cout << i << "--->";
        for (int j=0; j<adj[i].size(); j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
}


//returns the number of edges going out of a node
int Graph::num_edges_out(int v) {
    return adj[v].size();
}



//returns the number of edges going into a certain node
int Graph::num_edges_in(int v) {
    int cnt = 0;
    for (int i=0; i<adj.size(); i++)
        for (int j=0; j<adj[i].size(); i++)
            if (adj[i][j] == v) cnt++;
    return cnt;
}

int Graph::get_num_nodes() {
    return adj.size();
}


Graph Graph::get_transpose() {

    Graph g(V);

    for (int v=0; v<V; v++)
        for (auto u : adj[v]) g.add_edge(u, v);

    return g;

}
//takes an ID of a vertex, and returns the id's of all the verticies pointing to V
//note that this funciton is used with the transpose of the inital graph

vector<int> Graph::get_nodes_pointing_to_v(int V_id) {

    vector<int> ret;

    for (int i=0; i<adj[V_id].size(); i++) {
        //cout << "NOW PUSHING BACK: " << adj[V_id][i] << endl;
        ret.push_back(adj[V_id][i]);
    }

    return ret;
}


void Graph::displayGraph() {
    for(int i = 0; i<V; i++) {
        cout << i << "--->";
        for (int j=0; j<adj[i].size(); j++)
            cout << adj[i][j] << " ";
        cout << endl;
//            for (auto u : adj[i]) cout << u << " ";
//            cout << endl;
    }
}