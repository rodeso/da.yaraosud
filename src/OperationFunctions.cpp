#include "../include/OperationFunctions.h"
const int INF = INT_MAX;



//------------Backtracking Algorithm--------------------------------------------------------------------------------------------------------------------------------------------------



double OperationFunctions::distance(Graph<Node>& graph, Node src, Node dest) {
     for (auto u : graph.findVertex(src)->getAdj()){
         if (u->getDest()->getInfo().getIndex() == dest.getIndex()) {
             return u->getWeight();
         }
     }
     return INF;
}


void OperationFunctions::backtracking(Graph<Node>& graph, vector<int>& path, vector<int>& minpath, Node current_city, double& min_distance, double& total_distance) {
    if (path.size() == graph.getVertexSet().size()) {
        total_distance += distance(graph, current_city, Node(0,"N/A",{0.0,0.0})); 
        min_distance = min(min_distance, total_distance); 
        if (min_distance == total_distance) minpath = path;
        total_distance -= distance(graph, current_city, Node(0,"N/A",{0.0,0.0})); 
        return;
    }
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


void OperationFunctions::bound_2(Graph<Node>& graph) {
    Timer timer;
    vector<int> path;
    vector<int> minpath;
    double min_distance = INF;
    double total_distance = 0;

    timer.start();

    Node i = Node(0,"N/A",{0.0,0.0});
    path.push_back(i.getIndex());
    graph.findVertex(i)->setVisited(true);

    backtracking(graph, path, minpath, i, min_distance, total_distance);

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

            for (auto edge : vertex->getAdj()) {
                if (!edge->getDest()->isVisited()) {
                    pq.push({edge->getWeight(), edge->getDest()});
                }
            }

            previous=vertex;

        }
    }
    double ender = distance(graph, previous->getInfo(), startVertex->getInfo());
    MSTGraph.addEdge(previous->getInfo(),startVertex->getInfo(),ender);

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

    for (auto edge: previousVertex->getAdj()) {
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



//------------Alternative Heuristic and Real World--------------------------------------------------------------------------------------------------------------------------------------------------



Vertex<Node>* OperationFunctions::closestVertex(Vertex<Node>* current, Graph<Node> &graph, bool real) {
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


bool OperationFunctions::allVisited(Graph<Node> &graph) {
    bool flag = false;
    int i = 0;
    for (auto u : graph.getVertexSet()) {
        if (u->isVisited()) { i++; }
        if (i == graph.getVertexSet().size()) { flag = true; }
    }
    return flag;
}


vector<Vertex<Node>*> OperationFunctions::getOddVertexes(Graph<Node> &graph) {
    vector<Vertex<Node>*> oddVertexes;
    for (auto currentVertex : graph.getVertexSet()) {
        if (currentVertex->getAdj().size() % 2 != 0) {
            oddVertexes.push_back(currentVertex);
        }
    }
    return oddVertexes;
}


Graph<Node> OperationFunctions::findMWPM(Graph<Node> &graph, const vector<Vertex<Node>*>& oddVertexes, bool real) {
    Timer timer;
    Graph<Node> mwpm;
    timer.start();
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
                            break;
                        }
                    }
                    if (ExistsInReal) {
                        distance = distanceMinReal;
                    } else {
                        continue;
                    }
                } else {
                    distance = Haversine::calculate_distance(u->getInfo().getCoordinates().first, u->getInfo().getCoordinates().second, closest->getInfo().getCoordinates().first, closest->getInfo().getCoordinates().second);
                }
                mwpm.addEdge(u->getInfo(), closest->getInfo(), distance);
                mwpm.addEdge(closest->getInfo(), u->getInfo(), distance);
                u->setVisited(true);
                closest->setVisited(true);
            }
        }
    }
    cout << "Calculation of MWPM time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;

    return mwpm;
}


Graph<Node> OperationFunctions::combineGraphs(Graph<Node> &graph, Graph<Node> &MSTgraph, Graph<Node> &MWPM) {
    Timer timer;
    Graph<Node> combinedGraph = graph.getCopy();
    timer.start();

    for (auto vertex : combinedGraph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            combinedGraph.removeEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo());
        }
    }

    for (auto vertex : MSTgraph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            combinedGraph.addEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }
    for (auto vertex : MWPM.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
            combinedGraph.addEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }
    cout << "Calculation of CombinedGraph time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;

    return combinedGraph;
}


vector<int> OperationFunctions::findEulerianCircuit(Vertex<Node>* start) {
    Timer timer;
    vector<int> euler;
    if (!start) {
        return euler; 
    }
    timer.start();
    stack<Vertex<Node>*> havana;
    havana.push(start);
    while (!havana.empty()) {
        Vertex<Node>* v = havana.top();
        auto edges = v->getAdj();
        if (edges.empty()) {
            euler.push_back(v->getInfo().getIndex());
            havana.pop();
        } else {
            auto edge = edges.front();
            auto dest = edge->getDest();
            v->removeEdge(dest->getInfo());
            dest->removeEdge(v->getInfo());
            havana.push(dest);
        }
    }

    std::reverse(euler.begin(), euler.end());
    cout << "Calculation of EulerianCircuit time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;

    return euler;
}


vector<int> OperationFunctions::findHamiltonCircuit(vector<int>& eulerCircuit) {
    Timer timer;
    std::vector<int> hamilton;
    std::unordered_set<int> isVisited;
    timer.start();
    for (auto vert : eulerCircuit) {
        if (isVisited.count(vert) == 0 || hamilton.empty()) {
            hamilton.push_back(vert);
            isVisited.insert(vert);
        }
    }
    hamilton.push_back(0);
    cout << "Calculation of HamiltonCircuit time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;

    return hamilton;
}


void OperationFunctions::christofides(Graph<Node> &graph, int start, bool real) {
    Timer timer;
    vector<int> minpath;
    double min_distance = 0;
    timer.start();
    Graph<Node> MST = primsGraph(graph, start);
    vector<Vertex<Node>*> oddVertexes = getOddVertexes(graph);
    
    Graph<Node> MWPM = findMWPM(graph, oddVertexes, real);

    Graph<Node> combinedGraph = combineGraphs(graph, MST, MWPM);

    Node startNode(start, "N/A", {0.0,0.0});
    Vertex<Node>* starter = combinedGraph.findVertex(startNode);
    vector<int> eul = findEulerianCircuit(starter);
    vector<int> hamiltonianCircuit = findHamiltonCircuit(eul);

    minpath.clear();
    min_distance = 0;
    Vertex<Node>* previous = nullptr;


    for (auto vertex : hamiltonianCircuit) {
        minpath.push_back(vertex);
        if (previous != nullptr) {
            min_distance += distance(graph, previous->getInfo(), combinedGraph.findVertex(Node(vertex, "N/A", {0.0,0.0}))->getInfo());  
        }
        previous = combinedGraph.findVertex(Node(vertex,"N/A",{0.0,0.0}));
    }
    // Output the result
    cout << "Optimal Path: " << endl;
    for (int citeh : minpath) cout << citeh << " -> ";
    cout << "End of Journey \n";
    cout << "Minimum Distance: " << min_distance << endl;

    cout << "Calculation time: " << timer.elapsedMili()<< " Milliseconds (aprox. " << timer.elapsedSec() << " seconds)" << endl;


}


Vertex<Node>* OperationFunctions::getVertexRealWorldCoordinates(Graph<Node> &graph, double lon, double lat) {
    for (auto u : graph.getVertexSet()) {
        if (u->getInfo().getCoordinates().first == lon && u->getInfo().getCoordinates().second == lat) {
            return u;
        }
    }
    return nullptr;
}


















