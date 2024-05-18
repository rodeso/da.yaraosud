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
     * @brief Performs backtracking to find the minimum path in the graph. Complexity: O(n!)
     * @param graph The graph containing the nodes.
     * @param path The current path being explored.
     * @param minpath The minimum path found so far.
     * @param current_city The current city being visited.
     * @param min_distance The minimum distance found so far.
     * @param total_distance The total distance of the current path.
     */
    static void backtracking(Graph<Node> &graph, vector<int> &path, vector<int> &minpath, Node current_city, double &min_distance, double &total_distance);

    /**
     * @brief Applies the bound_2 algorithm to the graph. Complexity: O(n!)
     * @param graph The graph to apply the algorithm to.
     */
    static void bound_2(Graph<Node> &graph);

    /**
     * @brief Applies the Prim's algorithm to the graph and returns the minimum spanning tree. O(E log V)
     * @param graph The graph to apply the algorithm to.
     * @param i The index of the starting node.
     * @return The minimum spanning tree as a vector of vertices.
     */
    static vector<Vertex<Node> *> prims(Graph<Node> &graph, int i);

    /**
     * @brief Applies the Prim's algorithm to the graph and returns the minimum spanning tree as a new graph. Complexity: O(E log V)
     * @param graph The graph to apply the algorithm to.
     * @param i The index of the starting node.
     * @return The minimum spanning tree as a new graph.
     */
    static Graph<Node> primsGraph(Graph<Node> &graph, int i);

    /**
     * @brief Applies the tApprox algorithm to the graph. Complexity: O(E log V)
     * @param graph The graph to apply the algorithm to.
     */
    static void tApprox(Graph<Node> &graph);

    /**
     * @brief Gets the vertex in the graph with the specified real-world coordinates. O(1)
     * @param graph The graph to search in.
     * @param lat The latitude of the vertex.
     * @param lon The longitude of the vertex.
     * @return The vertex with the specified coordinates, or nullptr if not found.
     */
    static Vertex<Node> *getVertexRealWorldCoordinates(Graph<Node> &graph, double lat, double lon);

    /**
     * @brief Finds the closest vertex to the current vertex. Complexity: O(n)
     * @param current The current vertex.
     * @param graph The graph containing the vertices.
     * @param real Flag indicating whether to use real-world coordinates.
     * @return The closest vertex to the current vertex.
     */
    static Vertex<Node>* closestVertex(Vertex<Node>* current, Graph<Node> &graph, bool real);

    /**
     * @brief Checks if all vertices in the graph have been visited. Complexity: O(n)
     * @param graph The graph containing the vertices.
     * @return True if all vertices have been visited, false otherwise.
     */
    static bool allVisited(Graph<Node> &graph);

    /**
     * @brief Gets the odd-degree vertices in the graph. Complexity: O(n)
     * @param graph The graph containing the vertices.
     * @return A vector of odd-degree vertices.
     */
    static vector<Vertex<Node>*> getOddVertexes(Graph<Node> &graph);

    /**
     * @brief Finds the minimum weight perfect matching (MWPM) in the graph. Complexity: O(n^2)
     * @param graph The graph containing the vertices.
     * @param oddVertexes The odd-degree vertices.
     * @param real Flag indicating whether to use real-world coordinates.
     * @return The graph representing the MWPM.
     */
    static Graph<Node> findMWPM(Graph<Node> &graph, const vector<Vertex<Node>*>& oddVertexes, bool real);

    /**
     * @brief Combines the original graph, minimum spanning tree (MST), and MWPM into a single graph. Complexity: O(n)
     * @param graph The original graph.
     * @param MSTgraph The graph representing the MST.
     * @param MWPM The graph representing the MWPM.
     * @return The combined graph.
     */
    static Graph<Node> combineGraphs(Graph<Node> &graph, Graph<Node> &MSTgraph, Graph<Node> &MWPM);

    /**
     * @brief Finds the Eulerian circuit in the graph starting from the specified vertex. Complexity: O(n)
     * @param start The starting vertex.
     * @return The Eulerian circuit as a vector of vertex indices.
     */
    static vector<int> findEulerianCircuit(Vertex<Node>* start);

    /**
     * @brief Converts the Eulerian circuit into a Hamiltonian circuit. Complexity: O(n)
     * @param eulerCircuit The Eulerian circuit.
     * @return The Hamiltonian circuit as a vector of vertex indices.
     */
    static vector<int> findHamiltonCircuit(vector<int>& eulerCircuit);

    /**
     * @brief Applies the Christofides algorithm to the graph starting from the specified vertex. Complexity: O(n^2)
     * @param graph The graph to apply the algorithm to.
     * @param start The starting vertex.
     * @param real Flag indicating whether to use real-world coordinates.
     */
    static void christofides(Graph<Node> &graph, int start, bool real);

    //static void xApprox(Graph<Node> &graph);

};

#endif //YARAOSUD_OPERATIONFUNCTIONS_H