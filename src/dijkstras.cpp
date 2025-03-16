#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
   int n = G.numVertices;
    vector<int> distance;
    vector<bool> visited;
    distance.assign(n, INF);
    visited.assign(n, false);
    previous.assign(n, -1);
    using Node = pair<int, int>; 
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    distance[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue;
        }
        
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;

    if (destination == 0) {
        path.push_back(0);
        return path;
    }

    if (previous[destination] == -1) {
        return path; 
    }

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << endl;
        cout << "Total cost is " << total << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}