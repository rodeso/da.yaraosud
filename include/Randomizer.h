#ifndef YARAOSUD_RANDOMIZER_H
#define YARAOSUD_RANDOMIZER_H

#include "Include.h"
#include "Node.h"
#include "Graph.h"
class Randomizer {
    public:
        static int randInt(Graph<Node> &graph) {
            random_device rd; // obtain a random number from hardware
            mt19937 eng(rd()); // seed the generator
            uniform_int_distribution<> distr(0, graph.getVertexSet().size()); // define the range

            return distr(eng); // generate numbers
        }
};

#endif //YARAOSUD_RANDOMIZER_H
