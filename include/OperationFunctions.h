
#ifndef YARAOSUD_OPERATIONFUNCTIONS_H
#define YARAOSUD_OPERATIONFUNCTIONS_H
#include "Include.h"
#include "Graph.h"
#include "Node.h"

class OperationFunctions {
    private:

    public:
        static double distance(Graph<Node>& graph, Node src, Node dest);
        static void backtracking(Graph<Node>& graph, vector<Node>& path, Node current_city, double& min_distance, double& total_distance);
        static void solve_tsp(Graph<Node>& graph);

};


#endif //YARAOSUD_OPERATIONFUNCTIONS_H
