
#ifndef YARAOSUD_OPERATIONFUNCTIONS_H
#define YARAOSUD_OPERATIONFUNCTIONS_H
#include "Include.h"
#include "Graph.h"
#include "Node.h"
#include "Timer.h"
#include "Haversine.h"

class OperationFunctions {
private:

public:
    static double distance(Graph<Node> &graph, Node src, Node dest);

    static void backtracking(Graph<Node> &graph, vector<int> &path, vector<int> &minpath, Node current_city, double &min_distance, double &total_distance);

    static void bound_2(Graph<Node> &graph);

    static vector<Vertex<Node> *> prims(Graph<Node> &graph, int i);

    static void tApprox(Graph<Node> &graph);

    static Vertex<Node> *getVertexRealWorldCoordinates(Graph<Node> &graph, double lat, double lon);

    //static void xApprox(Graph<Node> &graph);

};

#endif //YARAOSUD_OPERATIONFUNCTIONS_H

