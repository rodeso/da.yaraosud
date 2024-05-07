#include "../include/OperationFunctions.h"
const int INF = INT_MAX;



//------------Backtracking Algorithm--------------------------------------------------------------------------------------------------------------------------------------------------



// Function to calculate the distance between two cities
double OperationFunctions::distance(Graph<Node>& graph, Node src, Node dest) {
    if(graph.findVertex(src)->getAdj().empty()) cout << src.getIndex() << "'s Adj is empty." << endl;
     for (auto u : graph.findVertex(src)->getAdj()){
         if (u->getDest()->getInfo().getIndex() == dest.getIndex()) {
             return u->getWeight();
         }
     }
     return INF;
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
void OperationFunctions::bound_tsp(Graph<Node>& graph) {
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

    cout << "Calculation time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;
}



//------------Triangular Approximation Heuristic--------------------------------------------------------------------------------------------------------------------------------------------------



vector<Vertex<Node>*> OperationFunctions::prims(Graph<Node> &graph) {
    Timer timer;
    Node i(0,"dummy",{0.0,0.0});
    Vertex<Node>* startVertex = graph.findVertex(i);
    priority_queue<pair<double, Vertex<Node>*>, vector<pair<double, Vertex<Node>*>>, greater<>> pq;
    vector<Vertex<Node>*> mst;
    timer.start();

    mst.push_back(startVertex);

    startVertex->setVisited(true);
    for (auto edge : startVertex->getAdj()) {
        pq.push({edge->getWeight(), edge->getDest()});
    }

    while (!pq.empty()) {
        auto [weight, vertex] = pq.top();
        pq.pop();
        if (!vertex->isVisited()) {
            vertex->setVisited(true);
            mst.push_back(vertex);

            // Add adjacent vertices to the priority queue
            for (auto edge : vertex->getAdj()) {
                if (!edge->getDest()->isVisited()) {
                    pq.push({edge->getWeight(), edge->getDest()});
                }
            }
        }
    }
    cout << "Calculation of MST time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;
    return mst;
}


void OperationFunctions::tApprox(Graph<Node> &graph) {
    Timer timer;
    Node i(0,"dummy",{0.0,0.0});
    vector<Vertex<Node>*> mst = prims(graph);

    vector<int> minpath;
    double min_distance=0;
    for (auto u : graph.getVertexSet()) {u->setVisited(false);}
    Vertex<Node>* previousVertex = nullptr;

    timer.start();

    //Isto abaixo está incompleto e não sei se está no caminho certo para o resultado, mas depois vamos ver
    for (auto vertex : mst) {
        if (previousVertex != nullptr) {

            bool vertex_is_neighbour=false;
            for (auto edge : previousVertex->getAdj()) {
                if (edge->getDest() == vertex) {
                    vertex_is_neighbour=true;
                    if (!vertex->isVisited()) {
                        vertex->setVisited(true);
                        minpath.push_back(vertex->getInfo().getIndex());
                        min_distance += edge->getWeight();
                        previousVertex = vertex;
                    }
                    break;
                }
            }
            if (!vertex_is_neighbour) {
                vertex->setVisited(true);
                minpath.push_back(vertex->getInfo().getIndex());
                min_distance+= 100; // random stuff while we dont have the haversine real thing implemented
                previousVertex = vertex;
            }


        } else {
            previousVertex = vertex;
            minpath.push_back(vertex->getInfo().getIndex());
        }
    }

    // Output the result
    cout << "Optimal Path: " << endl;
    for (int citeh : minpath) cout << citeh << " -> ";
    cout << "0 \n";
    cout << "Minimum Distance: " << min_distance << endl;

    cout << "Calculation time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;
}




























