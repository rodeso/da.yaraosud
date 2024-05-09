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



vector<Vertex<Node>*> OperationFunctions::prims(Graph<Node> &graph, int c) {
    Timer timer;
    Node i(c,"dummy",{0.0,0.0});
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
    vector<int> minpath;
    double min_distance=0;
    Vertex<Node>* previousVertex = nullptr;
    Vertex<Node>* startingVertex = nullptr;

    timer.start();
    vector<Vertex<Node>*> mst = prims(graph, 0);
    for (auto u : graph.getVertexSet()) {u->setVisited(false);};


    //This might work?? Or at least its close
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
                min_distance+= Haversine::calculate_distance(previousVertex->getInfo().getCoordinates().first, previousVertex->getInfo().getCoordinates().second, vertex->getInfo().getCoordinates().first, vertex->getInfo().getCoordinates().second); // random stuff while we dont have the haversine stuff implemented
                previousVertex = vertex;
            }


        } else {
            previousVertex = vertex;
            minpath.push_back(vertex->getInfo().getIndex());
            startingVertex= vertex;
        }
    }

    for (auto edge: previousVertex->getAdj()) { //adding the distance of returning back to Node 0
        if (edge->getDest()==startingVertex) {
            min_distance+=edge->getWeight();
        }
    }

    // Output the result
    cout << "Optimal Path: " << endl;
    for (int citeh : minpath) cout << citeh << " -> ";
    cout << "0 \n";
    cout << "Minimum Distance: " << min_distance << endl;

    cout << "Calculation time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;

}


//------------Alternative Heuristic--------------------------------------------------------------------------------------------------------------------------------------------------



Vertex<Node>* closestVertex(Vertex<Node>* current, Graph<Node> &graph) {
    double current_distance = INF;
    Vertex<Node>* current_node = nullptr;
    if (current->getInfo().getCoordinates().first == 0.0 && current->getInfo().getCoordinates().second == 0.0) {
        for (auto e : current->getAdj()) {
            if (e->getWeight() < current_distance) {
                current_distance = e->getWeight();
                current_node = e->getDest();

            }
        }
    }
    else {
        for (auto u : graph.getVertexSet()) {
            if (current_distance > Haversine::calculate_distance(current->getInfo().getCoordinates().first, current->getInfo().getCoordinates().second, u->getInfo().getCoordinates().first, u->getInfo().getCoordinates().second)) {
                current_distance = Haversine::calculate_distance(current->getInfo().getCoordinates().first, current->getInfo().getCoordinates().second, u->getInfo().getCoordinates().first, u->getInfo().getCoordinates().second);
                current_node = u;
            }
        }
    }

    return current_node;
}

bool allVisited(Graph<Node> &graph) {
    bool flag = false;
    int i = 0;
    for (auto u : graph.getVertexSet()) {
        if (u->isVisited()) { i++; }
        if (i == graph.getVertexSet().size()) { flag = true; }
    }
    return flag;
}




void OperationFunctions::divideAndConquer() {

}




void OperationFunctions::xApprox(Graph<Node> &graph) {
    Timer timer;
    vector<int> minpath;
    double min_distance=0;
    int important;
    stack<Vertex<Node>*> to_reset;
    Vertex<Node>* previousVertex = nullptr;
    Vertex<Node>* startingVertex = nullptr;

    timer.start();
    vector<Vertex<Node>*> mst = prims(graph, 0);
    for (auto u : graph.getVertexSet()) {u->setVisited(false);};

    bool there_is_closest = false;

    //This might work?? Or at least its close
    while (!allVisited(graph)) {

        for (auto vertex : mst) {
            if (previousVertex != nullptr) {

                if (closestVertex(previousVertex,graph)!=vertex) {
                    previousVertex->setVisited(false);
                    important = previousVertex->getInfo().getIndex();
                    there_is_closest=true;
                    break;
                }

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
                    min_distance+= Haversine::calculate_distance(previousVertex->getInfo().getCoordinates().first, previousVertex->getInfo().getCoordinates().second, vertex->getInfo().getCoordinates().first, vertex->getInfo().getCoordinates().second); // random stuff while we dont have the haversine stuff implemented
                    previousVertex = vertex;
                }

            } else {
                previousVertex = vertex;
                minpath.push_back(vertex->getInfo().getIndex());
                startingVertex= vertex;
            }
        }

        if (there_is_closest) {
            for (auto y : graph.getVertexSet()){
                if (!y->isVisited()) {
                    to_reset.push(y);
                }
            }
            mst = prims(graph, important);
            while (!to_reset.empty()) {
                auto z = to_reset.top();
                z->setVisited(false);
                to_reset.pop();
            }
            there_is_closest=false;
        }
    }

    for (auto edge: previousVertex->getAdj()) { //adding the distance of returning back to Node 0
        if (edge->getDest()==startingVertex) {
            min_distance+=edge->getWeight();
        }
    }

    // Output the result
    cout << "Optimal Path: " << endl;
    for (int citeh : minpath) cout << citeh << " -> ";
    cout << "0 \n";
    cout << "Minimum Distance: " << min_distance << endl;

    cout << "Calculation time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;
}



















