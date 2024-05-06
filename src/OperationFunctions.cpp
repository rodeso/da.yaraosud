#include "../include/OperationFunctions.h"
const int INF = INT_MAX;

// Function to calculate the distance between two cities
double OperationFunctions::distance(Graph<Node>& graph, Node src, Node dest) {
    if(graph.findVertex(src)->getAdj().empty()) cout << src.getIndex() << "'s Adj is empty." << endl;
     for (auto u : graph.findVertex(src)->getAdj()){
         if (u->getDest()->getInfo().getIndex() == dest.getIndex()) {
             return u->getWeight();
         }
     }
     return -INF;
}

// Backtracking function to find the minimum distance
void OperationFunctions::backtracking(Graph<Node>& graph, vector<int>& path, vector<int>& minpath, Node current_city, double& min_distance, double& total_distance) {
    // If all cities have been visited
    if (path.size() == graph.getVertexSet().size()) {
        total_distance += distance(graph, current_city, Node(0,"N/A",{0.0,0.0})); // Return to the starting city
        min_distance = min(min_distance, total_distance); // Update minimum distance
        if (min_distance == total_distance) minpath = path; // If path is the best, save it
        total_distance -= distance(graph, current_city, Node(0,"N/A",{0.0,0.0})); // Backtrack
        return;
    }
    // Loop through all unvisited cities
    for (Edge<Node>* edge : graph.findVertex(current_city)->getAdj()) {
        Vertex<Node>* currentNeighbour = edge->getDest();
        if (!currentNeighbour->isVisited()) {
            double distance = edge->getWeight();
            if(total_distance + distance >= min_distance) {continue;}

            path.push_back(currentNeighbour->getInfo().getIndex());
            currentNeighbour->setVisited(true);
            total_distance += distance;

            backtracking(graph, path, minpath, currentNeighbour->getInfo(), min_distance, total_distance);

            path.pop_back();
            currentNeighbour->setVisited(false);
            total_distance -= distance;
        }
    }
}

// Main function to solve TSP using backtracking
void OperationFunctions::solve_tsp(Graph<Node>& graph) {
    Timer timer;
    vector<int> path;
    vector<int> minpath;
    double min_distance = INF;
    double total_distance = 0;

    timer.start();

    // Start from the first city
    Node i = Node(0,"N/A",{0.0,0.0});
    path.push_back(i.getIndex());
    graph.findVertex(i)->setVisited(true);

    // Call the backtracking function
    backtracking(graph, path, minpath, i, min_distance, total_distance);

    // Output the result
    cout << "Optimal Path: " << endl;
    for (int citeh : minpath) cout << citeh << " -> ";
    cout << "0 \n";
    cout << "Minimum Distance: " << min_distance << endl;

    cout << "Calculation time: " << timer.elapsed()<< " Milliseconds\n";
}

