/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 *
 * @param graph - the graph to search
 * @return the minimum edge weight
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    // TODO
    // 1. Label all edges and vertices as unexplored. You will need
    //    to look in graph.h for the right functions.

    string label = "UNEXPLORED";

    vector<Vertex> v = graph.getVertices();
    for(size_t i = 0; i < v.size(); i++){
        graph.setVertexLabel(v[i], label);
    }
    vector<Edge> e = graph.getEdges();
    for(size_t i = 0; i < e.size(); i++){
        graph.setEdgeLabel(e[i].source, e[i].dest, label);
    }


    // 2. Use the BFS function in graph_tools to find the minimum edge.
    //    Don't forget to label it.
    Edge edgeWithMinWeight = BFS(graph, graph.getStartingVertex());
    graph.setEdgeLabel(edgeWithMinWeight.source, edgeWithMinWeight.dest, "MIN");


    return edgeWithMinWeight.weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    unordered_map<Vertex, Vertex> parent;

    // TODO
    // 1. Set all vertices as unexplored

    vector<Vertex> v = graph.getVertices();
    for(size_t i = 0; i < v.size(); i++){
        graph.setVertexLabel(v[i], "UNEXPLORED");
    }

    // 2. Do a modified BFS. See the BFS function below as a guideline, but
    //    your BFS here only needs to populate the "parent" map and stop once the short-
    //    est path has been found.

    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);

        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                parent[adj[i]] = v;
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                if(adj[i] == end){
                    break;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
            }
        }
    }

    // 3. Use the unordered map to trace from a path from the end to the start,
    //    counting edges. You should set edges to "minpath" here too.

    Vertex temp = end;
    int dist = 0;
    while(temp != start){
        dist++;
        // auto it = parent.find(temp);
        // graph.setEdgeLabel(temp, it->second, "MINPATH");
        // temp = it->second;
        graph.setEdgeLabel(temp, parent[temp], "MINPATH");
        temp = parent[temp];
    }

    return dist;
}








/**
 * Finds a minimal spanning tree on a graph.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class given in dsets.cpp to help you with
 *  Kruskal's algorithm.
 *
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
     vector<Edge> edges = graph.getEdges();
     selectionSort(edges);

     vector<Vertex> vertices = graph.getVertices();
     DisjointSets dSet; 
     dSet.addelements(vertices.size());



     size_t counter = 0;
     while(counter != vertices.size() - 1){
        Edge e = edges.front();
        

        Vertex s = e.source;
        Vertex d = e.dest;
    

        if(dSet.find(getIndex(vertices, s)) != dSet.find(getIndex(vertices, d))){
            dSet.setunion(dSet.find(getIndex(vertices, s)), dSet.find(getIndex(vertices, d)));
            counter++;
            graph.setEdgeLabel(s, d, "MST");
        }
        
        edges.erase(edges.begin());
     }
}


void GraphTools::selectionSort(vector<Edge>& arr){
    int min;
    for(size_t i = 0; i < arr.size() - 1; i++){
        min = i;

        for(size_t j = i+1; j < arr.size(); j++){
            if(arr[j].weight < arr[min].weight){
                min = j;
            }
        }

        if(min != i){
            std::swap(arr[min], arr[i]);
        }
    }
}


int GraphTools:: getIndex(vector<Vertex> arr, Vertex v){
    auto it = find(arr.begin(), arr.end(), v);
    
    int index = 0;
    if (it != arr.end()) {
        return it - arr.begin();
    } else{
        return -1;
    }
}





/**
 * Does a BFS of a graph, keeping track of the minimum
 *  weight edge seen so far.
 * @param g - the graph
 * @param start - the vertex to start the BFS from
 * @return the minimum weight edge
 */
Edge GraphTools::BFS(Graph& graph, Vertex start)
{
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Edge min;
    min.weight = INT_MAX;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            }
        }
    }
    return min;
}
