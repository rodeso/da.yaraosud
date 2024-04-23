#ifndef YAATWSM_MENU_H
#define YAATWSM_MENU_H
#include "Include.h"
#include "Graph.h"
#include "Node.h"
#include "ReadFunctions.h"
#include "OperationFunctions.h"

/**
 * @brief Class that represents the system menus' interface and all of its stored data.
 */

class Menu {

    private:
        /**
        * @brief Graph structure.
        */
        Graph<Node> graph;
        /**
        * @brief Dictionary to help relate the names of the cities with its respective code.
        */
        unordered_map<string,string> cityDict;

    public:
        /**
         * @brief Function to initialize the menu
         */
        void run();
        /**
         * @brief Function to initialize the case 1 of the menu
         */
        void case1();
        /**
         * @brief Function to initialize the case 2 of the menu
         */
        void case2();
        /**
         * @brief Function to initialize the case 3 of the menu
         */
        void case3();
        /**
         * @brief Function to initialize the case 4 of the menu
         */
        void case4();
        /**
         * @brief Function to initialize the case 5 of the menu
         */
        void case5();
        /**
         * @brief Function to initialize the case 6 of the menu
         */
        void case6();
        /**
         * @brief Function to initialize the case 7 of the menu
         */
        void case7();
        /**
         * @brief Function to initialize the case 8 of the menu
         */
        void case8();
        /**
         * @brief Function to initialize the case 9 of the menu
         */
        void case9();
};


#endif //YAATWSM_MENU_H
