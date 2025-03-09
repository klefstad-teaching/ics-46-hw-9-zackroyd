#include "dijkstras.h"
#include <iostream>

struct VertexWeight {
    int vertex;
    int weight;
    friend bool operator<(const VertexWeight& first, const VertexWeight& other) {
        return first.weight > other.weight;
    }
};


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distances(n, INF);
    distances[source] = 0;
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    priority_queue<VertexWeight> pq;
    pq.push(VertexWeight{source, 0});
    
    while (!pq.empty()) {
        VertexWeight current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(VertexWeight{v, distances[v]});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    stack<int> reversed_result;
    vector<int> result;
    vector<int> d = distances;
    for (int curr = destination; curr != -1; curr = previous[curr]) {
        reversed_result.push(curr);
        if (reversed_result.size() > distances.size()) while (!reversed_result.empty()) reversed_result.pop();
    }
    while (!reversed_result.empty()) {
        result.push_back(reversed_result.top());
        reversed_result.pop();
    }
    return result;
}

void print_path(const vector<int>& v, int total) {
    for (int i : v) std::cout << i << ' ';
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}