#include "dijkstras.h"
#include <iostream>

int main() {
    std::string filename = "src/large.txt";
    Graph G;
    file_to_graph(filename, G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 1, previous);
    for (size_t i = 0; i < G.size(); ++i) print_path(extract_shortest_path(distances, previous, i), distances[i]);
}
