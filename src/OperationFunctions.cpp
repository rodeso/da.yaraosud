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
void OperationFunctions::bound_2(Graph<Node>& graph) {
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


Graph<Node> OperationFunctions::primsGraph(Graph<Node> &graph, int c) {
    Timer timer;
    Node i(c,"dummy",{0.0,0.0});
    Vertex<Node>* startVertex = graph.findVertex(i);
    priority_queue<pair<double, Vertex<Node>*>, vector<pair<double, Vertex<Node>*>>, greater<>> pq;

    Vertex<Node>* previous;
    Graph<Node> MSTGraph;

    timer.start();

    MSTGraph.addVertex(startVertex->getInfo());
    previous=startVertex;

    startVertex->setVisited(true);
    for (auto edge : startVertex->getAdj()) {
        pq.push({edge->getWeight(), edge->getDest()});
    }

    while (!pq.empty()) {
        auto [weight, vertex] = pq.top();
        pq.pop();
        if (!vertex->isVisited()) {
            vertex->setVisited(true);
            MSTGraph.addVertex(vertex->getInfo());
            MSTGraph.addEdge(previous->getInfo(), vertex->getInfo(), distance(graph,previous->getInfo(),vertex->getInfo()));
            MSTGraph.addEdge(vertex->getInfo(), previous->getInfo(), distance(graph,previous->getInfo(),vertex->getInfo()));

            // Add adjacent vertices to the priority queue
            for (auto edge : vertex->getAdj()) {
                if (!edge->getDest()->isVisited()) {
                    pq.push({edge->getWeight(), edge->getDest()});
                }
            }

            previous=vertex;

        }
    }
    cout << "Calculation of MST time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;
    return MSTGraph;
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
                if (vertex->getInfo().getCoordinates().first == 0.0 && vertex->getInfo().getCoordinates().second == 0.0) {break;}//Do not come, do not come
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



Vertex<Node>* closestVertex(Vertex<Node>* current, Graph<Node> &graph, bool real) {
    double current_distance = INF;
    Vertex<Node>* closest_node = nullptr;
    if (current->getInfo().getCoordinates().first == 0.0 && current->getInfo().getCoordinates().second == 0.0) {
        for (auto e : current->getAdj()) {
            if (e->getWeight() < current_distance) {
                current_distance = e->getWeight();
                closest_node = e->getDest();

            }
        }
    }
    else {
        if (!real) {
            for (auto u : graph.getVertexSet()) {
                if (current_distance > Haversine::calculate_distance(current->getInfo().getCoordinates().first, current->getInfo().getCoordinates().second, u->getInfo().getCoordinates().first, u->getInfo().getCoordinates().second)) {
                    current_distance = Haversine::calculate_distance(current->getInfo().getCoordinates().first, current->getInfo().getCoordinates().second, u->getInfo().getCoordinates().first, u->getInfo().getCoordinates().second);
                    closest_node = u;
                }
            }
        }
    }

    return closest_node;
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

vector<Vertex<Node>*> getOddVertexes(Graph<Node> &graph) {
    vector<Vertex<Node>*> oddVertexes;
    for (auto currentVertex : graph.getVertexSet()) {
        if (currentVertex->getAdj().size() % 2 != 0) {
            oddVertexes.push_back(currentVertex);
        }
    }
    if (oddVertexes.size() % 2 == 0) {cout << "Wow there are an even number of odd vertexes, this is a rare sight" << endl;}
    return oddVertexes;
}

Graph<Node> findMWPM(Graph<Node> &graph, const vector<Vertex<Node>*>& oddVertexes, bool real) {
    Graph<Node> mwpm;
    for (auto u : oddVertexes) {
        if (!u->isVisited()) {
            Vertex<Node>* closest = closestVertex(u, graph, real);
            bool ExistsInOdd = false;
            
            for(auto d : oddVertexes) {if (d == closest && !closest->isVisited()) {ExistsInOdd = true;}}
            if (!ExistsInOdd) {continue;}
            
            if (closest != nullptr) {
                double distance;
                if (real || (closest->getInfo().getCoordinates().first == 0.0 && closest->getInfo().getCoordinates().second == 0.0)) {
                    bool ExistsInReal = false;
                    double distanceMinReal = 0.0;
                    for (auto e : u->getAdj()) {
                        if (e->getDest() == closest) {
                            distanceMinReal = e->getWeight();
                            ExistsInReal = true;
                            break; // Found the edge, no need to continue searching
                        }
                    }
                    if (ExistsInReal) {
                        distance = distanceMinReal;
                    } else {
                        continue; // If no real edge exists and it's required, skip this pair
                    }
                } else {
                    distance = Haversine::calculate_distance(u->getInfo().getCoordinates().first, u->getInfo().getCoordinates().second, closest->getInfo().getCoordinates().first, closest->getInfo().getCoordinates().second);
                }
                // Add edge from u to closest
                mwpm.addEdge(u->getInfo(), closest->getInfo(), distance);
                // Add edge from closest back to u to ensure bidirectionality
                mwpm.addEdge(closest->getInfo(), u->getInfo(), distance);
                u->setVisited(true);
                closest->setVisited(true);
            }
        }
    }
    return mwpm;
}
Graph<Node> combineGraphs(Graph<Node> &graph, vector<Vertex<Node>*> &MST, Graph<Node> &MWPM) {
    // Create a new graph that includes all vertices from the original graph
    Graph<Node> combinedGraph = graph;

    // Remove all edges from the combinedGraph
    for (auto vertex : combinedGraph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            combinedGraph.removeEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo());
        }
    }

    // Add the edges from the MST to the combinedGraph
    Vertex<Node>* previousVertex = nullptr;
    for (auto vertex : MST) {
        if (previousVertex != nullptr) {
            for (auto edge : previousVertex->getAdj()) {
                if (edge->getDest() == vertex) {
                    combinedGraph.addEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
                    break;
                }
            }
        }
        previousVertex = vertex;
    }

    // Add the edges from the MWPM to the combinedGraph
    for (auto vertex : MWPM.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            combinedGraph.addEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }

    return combinedGraph;
}

vector<int> findEulerianCircuit(Graph<Node>& combinedGraph, Vertex<Node>* start) {
    vector<int> euler;
    if (!start) {
        return euler; // Return empty if start is null
    }

    stack<Vertex<Node>*> havana;
    havana.push(start);
    while (!havana.empty()) {
        Vertex<Node>* v = havana.top();
        cout << v->getInfo().getIndex() << endl;
        auto edges = v->getAdj(); // Get a reference to avoid copying
        if (edges.empty()) {
            euler.push_back(v->getInfo().getIndex());
            havana.pop();
        } else {
            auto edge = edges.front();
            auto dest = edge->getDest();
            // Assuming removeEdge correctly handles edge removal in both directions if needed
            v->removeEdge(dest->getInfo());
            dest->removeEdge(v->getInfo()); // If the graph is undirected
            havana.push(dest);
        }
    }

    std::reverse(euler.begin(), euler.end());
    return euler;
}

vector<int> findHamiltonCircuit(vector<int>& eulerCircuit) {
    std::vector<int> hamilton;
    std::unordered_set<int> isVisited;

    for (auto vert : eulerCircuit) {
        if (isVisited.count(vert) == 0 || hamilton.empty()) {
            hamilton.push_back(vert);
            isVisited.insert(vert);
        }
    }

    if (!hamilton.empty()) {
        hamilton.push_back(hamilton[0]);
    }

    return hamilton;
}

void OperationFunctions::christofides(Graph<Node> &graph, Vertex<Node> *start, bool real) {
    Timer timer;
    vector<int> minpath;
    double min_distance = 0;
    timer.start();
    vector<Vertex<Node>*> MST = prims(graph, start->getInfo().getIndex());
    vector<Vertex<Node>*> oddVertexes = getOddVertexes(graph);
    
    Graph<Node> MWPM = findMWPM(graph, oddVertexes, real);

    Graph<Node> combinedGraph = combineGraphs(graph, MST, MWPM);

    vector<int> eul = findEulerianCircuit(combinedGraph, start);
    // Convert Eulerian circuit to Hamiltonian circuit
    vector<int> hamiltonianCircuit = findHamiltonCircuit(eul);


    // Calculate minimum path and distance
    minpath.clear();
    min_distance = 0;
    Vertex<Node>* previous = nullptr;
    for (auto vertex : hamiltonianCircuit) {
        minpath.push_back(vertex);
        if (previous) {
            min_distance += distance(graph, previous->getInfo(), graph.findVertex(Node(vertex, "N/A", {0.0,0.0}))->getInfo());  // Using your distance function
        }
        previous = graph.findVertex(Node(vertex,"N/A",{0.0,0.0}));
    }
    // Output the result
    cout << "Optimal Path: " << endl;
    for (int citeh : minpath) cout << citeh << " -> ";
    cout << "0 \n";
    cout << "Minimum Distance: " << min_distance << endl;

    cout << "Calculation time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;

    




}












//------------Real World--------------------------------------------------------------------------------------------------------------------------------------------------


Vertex<Node>* OperationFunctions::getVertexRealWorldCoordinates(Graph<Node> &graph, double lat, double lon) {
    for (auto u : graph.getVertexSet()) {
        if (u->getInfo().getCoordinates().first == lat && u->getInfo().getCoordinates().second == lon) {
            return u;
        }
    }
    return nullptr;
}















