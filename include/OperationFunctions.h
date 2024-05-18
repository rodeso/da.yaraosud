
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
    static Graph<Node> primsGraph(Graph<Node> &graph, int i);


    static void tApprox(Graph<Node> &graph);

    static Vertex<Node> *getVertexRealWorldCoordinates(Graph<Node> &graph, double lat, double lon);

    static void christofides(Graph<Node> &graph, Vertex<Node> *start, bool real);

    //static void xApprox(Graph<Node> &graph);

};

#endif //YARAOSUD_OPERATIONFUNCTIONS_H

/**
 * @file OperationFunctions.h
 * @brief This file contains the declaration of the OperationFunctions class.
 */

#ifndef YARAOSUD_OPERATIONFUNCTIONS_H
#define YARAOSUD_OPERATIONFUNCTIONS_H

#include "Include.h"
#include "Graph.h"
#include "Node.h"
#include "Timer.h"
#include "Haversine.h"

/**
 * @class OperationFunctions
 * @brief The OperationFunctions class contains various operations related to graph manipulation.
 */
class OperationFunctions {
private:

public:
    /**
     * @brief Calculates the distance between two nodes in the graph.
     * @param graph The graph containing the nodes.
     * @param src The source node.
     * @param dest The destination node.
     * @return The distance between the source and destination nodes.
     */
    static double distance(Graph<Node> &graph, Node src, Node dest);

    /**
     * @brief Performs backtracking to find the minimum path in the graph.
     * @param graph The graph containing the nodes.
     * @param path The current path being explored.
     * @param minpath The minimum path found so far.
     * @param current_city The current city being visited.
     * @param min_distance The minimum distance found so far.
     * @param total_distance The total distance of the current path.
     */
    static void backtracking(Graph<Node> &graph, vector<int> &path, vector<int> &minpath, Node current_city, double &min_distance, double &total_distance);

    /**
     * @brief Applies the bound_2 algorithm to the graph.
     * @param graph The graph to apply the algorithm to.
     */
    static void bound_2(Graph<Node> &graph);

    /**
     * @brief Applies the Prim's algorithm to the graph and returns the minimum spanning tree.
     * @param graph The graph to apply the algorithm to.
     * @param i The index of the starting node.
     * @return The minimum spanning tree as a vector of vertices.
     */
    static vector<Vertex<Node> *> prims(Graph<Node> &graph, int i);

    /**
     * @brief Applies the Prim's algorithm to the graph and returns the minimum spanning tree as a new graph.
     * @param graph The graph to apply the algorithm to.
     * @param i The index of the starting node.
     * @return The minimum spanning tree as a new graph.
     */
    static Graph<Node> primsGraph(Graph<Node> &graph, int i);

    /**
     * @brief Applies the tApprox algorithm to the graph.
     * @param graph The graph to apply the algorithm to.
     */
    static void tApprox(Graph<Node> &graph);

    /**
     * @brief Gets the vertex in the graph with the specified real-world coordinates.
     * @param graph The graph to search in.
     * @param lat The latitude of the vertex.
     * @param lon The longitude of the vertex.
     * @return The vertex with the specified coordinates, or nullptr if not found.
     */
    static Vertex<Node> *getVertexRealWorldCoordinates(Graph<Node> &graph, double lat, double lon);

    /**
     * @brief Applies the Christofides algorithm to the graph starting from the specified vertex.
     * @param graph The graph to apply the algorithm to.
     * @param start The starting vertex.
     * @param real Flag indicating whether to use real-world coordinates.
     */
    static void christofides(Graph<Node> &graph, Vertex<Node> *start, bool real);

    //static void xApprox(Graph<Node> &graph);

};

#endif //YARAOSUD_OPERATIONFUNCTIONS_H