#ifndef YARAOSUD_READFUNCTIONS_H
#define YARAOSUD_READFUNCTIONS_H
#include "Include.h"
#include "Graph.h"
#include "Node.h"

/**
 * @brief Class that represents the functions related to the reading and organizing of the system data.
 */

/**
 * @class ReadFunctions
 * @brief A class that provides functions for reading different types of graphs.
 */
class ReadFunctions {
    private:

    public:
        /**
         * @brief Reads a toy graph.
         * @param i The index of the toy graph to read.
         * @return The graph read from the file.
         */
        static Graph<Node> readToy(int i);

        /**
         * @brief Reads an extra graph.
         * @param i The index of the extra graph to read.
         * @return The graph read from the file.
         */
        static Graph<Node> readExtra(int i);

        /**
         * @brief Reads a real graph.
         * @param i The index of the real graph to read.
         * @return The graph read from the file.
         */
        static Graph<Node> readReal(int i);
};



#endif //YARAOSUD_READFUNCTIONS_H
