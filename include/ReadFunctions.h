#ifndef YAATWSM_READFUNCTIONS_H
#define YAATWSM_READFUNCTIONS_H
#include "Include.h"
#include "Graph.h"
#include "Node.h"

/**
 * @brief Class that represents the functions related to the reading and organizing of the system data.
 */

class ReadFunctions {
    private:

    public:
        /**
        * @brief Function that reads all the Reservoirs information in the selected data folder, allowing for the creation of the nodes of its type, and the population of the graph.
        * @details Complexity O(V)
        */
        static vector<Node> readReservoirs(string const &pathname);
        /**
        * @brief Function that reads all the Cities information in the selected data folder, allowing for the creation of the nodes of its type, and the population of the graph and the dictionary.
        * @details Complexity O(V)
        */
        static vector<Node> readCities(unordered_map<string,string> &cityDict, string const &pathname);
        /**
        * @brief Function that reads all the Stations information in the selected data folder, allowing for the creation of the nodes of its type, and the population of the graph.
        * @details Complexity O(V)
        */
        static vector<Node> readStations(string const &pathname);
        /**
        * @brief Function that reads all the Pipes information in the selected data folder, allowing for the creation of the edges in the graph.
        * @details Complexity O(V+E)
        */
        static void readPipes(Graph<Node>& graph, string const &pathname);
};



#endif //YAATWSM_READFUNCTIONS_H
