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
        static Graph<Node> readToy(int i);
        static Graph<Node> readExtra(int i);
        static Graph<Node> readReal(int i);
};



#endif //YARAOSUD_READFUNCTIONS_H
