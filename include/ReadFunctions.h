#ifndef YARAOSUD_READFUNCTIONS_H
#define YARAOSUD_READFUNCTIONS_H
#include "Include.h"
#include "Graph.h"
#include "Node.h"

/**
 * @brief Class that represents the functions related to the reading and organizing of the system data.
 */

class ReadFunctions {
    private:

    public:
        Graph<Node> readToy(int i);
        Graph<Node> readExtra(int i);
};



#endif //YARAOSUD_READFUNCTIONS_H
