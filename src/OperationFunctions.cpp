#include "../include/OperationFunctions.h"
const int INF = INT_MAX;

// Function to calculate the distance between two cities
double OperationFunctions::distance(Graph<Node>& graph, Node src, Node dest) {
    if(graph.findVertex(src)->getAdj().empty()) cout << "WHJAAAAA";
     for (auto u : graph.findVertex(src)->getAdj()){
         if (u->getDest()->getInfo().getIndex() == dest.getIndex()) {
             return u->getWeight();
         }
     }
     return -10000000;
}

// Backtracking function to find the minimum distance
void OperationFunctions::backtracking(Graph<Node>& graph, vector<Node>& path, Node current_city, double& min_distance, double& total_distance) {
    // If all cities have been visited
    if (path.size() == graph.getVertexSet().size()) {
        total_distance += distance(graph, current_city, Node(0,"N/A",{0.0,0.0})); // Return to the starting city
        min_distance = min(min_distance, total_distance); // Update minimum distance
        total_distance -= distance(graph, current_city, Node(0,"N/A",{0.0,0.0})); // Backtrack
        return;
    }

    // Loop through all unvisited cities
    for (auto i: graph.getVertexSet()) {
        if (!i->isVisited()) {
            int dist_to_next_city = distance(graph, current_city, i->getInfo());
            // Pruning: if the total distance + distance to next city is already greater than the current minimum distance, skip this path
            if (total_distance + dist_to_next_city >= min_distance)
                continue;

            path.push_back(i->getInfo());
            i->setVisited(true);
            total_distance += dist_to_next_city;

            backtracking(graph, path, i->getInfo(), min_distance, total_distance);

            path.pop_back();
            i->setVisited(false);
            total_distance -= dist_to_next_city;
        }
    }
}

// Main function to solve TSP using backtracking
void OperationFunctions::solve_tsp(Graph<Node>& graph) {
    for (auto u : graph.getVertexSet()) {
        u->setVisited(false);
    }

    vector<Node> path;
    double min_distance = INF;
    double total_distance = 0;

    // Start from the first city
    Node i = Node(0,"N/A",{0.0,0.0});
    path.push_back(i);
    graph.findVertex(i)->setVisited(true);

    // Call the backtracking function
    backtracking(graph, path, i, min_distance, total_distance);

    // Output the result
    cout << "Optimal Path: ";
    for (Node city : path) {
        city.print();
    }
    cout << "Minimum Distance: " << min_distance << endl;
}

