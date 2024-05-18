#include "../include/Menu.h"
void waitForInput() {
    string input;
    getline(std::cin, input); 
}

void Menu::run() {
    graph = Graph<Node>();

    while (true) {
        string decision;
        string csv_number;
        int i;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Welcome to the Ocean Shipping and Urban Deliveries Routing Algorithm Tool!" << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Select your data folder:" << endl;
        cout << "1 - Toy." << endl;
        cout << "2 - Extra Medium." << endl;
        cout << "3 - Real-world." << endl;
        cout << "0 - Exit." << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Please select the task you wish to perform by inputting its number: ";

        while (true) {
            getline(cin, decision);
            cout << endl;
            if (decision.size() != 1) { cout << "Invalid input. Please enter a number between 0 and 3: "; continue;}
            switch (decision[0]) {
                case '1':
                    cout << string(LINE_SIZE_, '-') << endl;
                    cout << "Toy data sets:" << endl;
                    cout << "0 - Shipping." << endl;
                    cout << "1 - Stadiums." << endl;
                    cout << "2 - Tourism." << endl;
                    cout << string(LINE_SIZE_, '-') << endl;
                    cout << "Please enter the number of the desired Toy data set: ";
                    getline(cin, csv_number);
                    graph = ReadFunctions::readToy(stoi(csv_number));

                    for (auto u : graph.getVertexSet()) {
                        u->getInfo().print();
                        for (auto e : u->getAdj()) {
                            cout << "Edge From: " <<  e->getOrig()->getInfo().getIndex() << " To " << e->getDest()->getInfo().getIndex() << " (" << e->getWeight() << ")" << endl;
                        }
                    }

                    goto load;
                case '2':
                    cout << "Available Extra Medium data sets: 25,50,75,100,200,300,400,500,600,700,800,900" << endl;
                    cout << "Please enter the number of the desired Extra Medium data set: ";
                    getline(cin, csv_number);
                    i = stoi(csv_number);
                    if (i != 25 && i != 50 && i != 75 && i != 100 && i != 200 && i != 300 && i != 400 && i != 500 && i != 600 && i != 700 && i != 800 && i != 900) { cout << "Error: Extra csv number doesn't exist."; break;}
                    graph = ReadFunctions::readExtra(i);
                    for (auto u : graph.getVertexSet()) {
                        u->getInfo().print();
                    }
                    goto load;
                case '3':
                    cout << "Available Graphs: 1, 2 and 3 (ATTENTION: GRAPH 3 MAY LOAD SLOWLY)" << endl;
                    cout << "Please enter the number of the desired Graph data set: ";
                    getline(cin, csv_number);
                    graph = ReadFunctions::readReal(stoi(csv_number));
                    for (auto u : graph.getVertexSet()) {
                        u->getInfo().print();
                    }
                    goto real;
                case '0':
                    cout << "Goodbye!" << endl;
                    exit(0);
                default:
                    cout << "Invalid input. Please enter a number between 0 and 3: ";
                    break;
            }
        }
        load:

        break;
    }
    while (true) {
        string decision;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Select your operation:" << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "1 - Backtracking Algorithm." << endl;
        cout << "2 - Triangular Approximation Heuristic." << endl;
        cout << "3 - Alternative Heuristic." << endl;
        cout << "9 - Credits." << endl;
        cout << "0 - Exit." << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Please select the task you wish to perform by inputting its number: ";
        for (auto u : graph.getVertexSet()) {u->setVisited(false);}
        getline(cin, decision);
        cout << string(LINE_SIZE_, '-') << endl;
        cout << endl;
        if (decision.size() != 1) {
            cout << "Invalid input. Please enter a number between 0 and 5: " << endl;
            continue;
        }
        switch (decision[0]) {
            case '1':
                case1();
                waitForInput();
                break;
            case '2':
                case2();
                waitForInput();
                break;
            case '3':
                case3();
                waitForInput();
                break;
            case '4':
                case4();
                waitForInput();
                break;
            case '9':
                case9();
                waitForInput();
                break;
            case '0':
                cout << "Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid input. Please enter a number between 0 and 5: " << endl;
                break;
        }
    }
    real:
    while (true) {
        string decision;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Select Starting Point:" << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "1 - Random." << endl;
        cout << "2 - ID." << endl;
        cout << "3 - Coordinates." << endl;
        cout << "0 - Exit." << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Please select the task you wish to perform by inputting its number: ";
        for (auto u : graph.getVertexSet()) {u->setVisited(false);}
        getline(cin, decision);
        cout << string(LINE_SIZE_, '-') << endl;
        cout << endl;
        if (decision.size() != 1) {
            cout << "Invalid input. Please enter a number between 0 and 5: " << endl;
            continue;
        }
        switch (decision[0]) {
            case '1':
                case5();
                waitForInput();
                break;
            case '2':
                case6();
                waitForInput();
                break;
            case '3':
                case7();
                waitForInput();
                break;
            case '0':
                cout << "Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid input. Please enter a number between 0 and 3: " << endl;
                break;
        }
    }
}


void Menu::case1() {
    OperationFunctions::bound_2(graph);
}


void Menu::case2() {
    OperationFunctions::tApprox(graph);
}


void Menu::case3() {
    OperationFunctions::christofides(graph, 0, false);
}


void Menu::case4() {
}


void Menu::case5() {
    OperationFunctions::christofides(graph, Randomizer::randInt(graph), true);
}


void Menu::case6() {
    string id;
    cout << "Please enter the ID of the desired starting point: ";
    getline(cin, id);
    OperationFunctions::christofides(graph, stoi(id), true);
}


void Menu::case7() {
    string x, y;
    cout << "Please enter the Longitude coordinate of the desired starting point: ";
    getline(cin, x);
    cout << "Please enter the Latitude coordinate of the desired starting point: ";
    getline(cin, y);
    Vertex<Node>* start = OperationFunctions::getVertexRealWorldCoordinates(graph, stod(x), stod(y));
    OperationFunctions::christofides(graph, start->getInfo().getIndex(), true);
}


void Menu::case9() {
    cout << "This program was created by:" << endl;
    cout << string(2*(LINE_SIZE_/5), ' ');
    cout << "Afonso Pedro Maia de Castro (up202208026@up.pt)" << endl;
    cout << string(2*(LINE_SIZE_/5), ' ');
    cout << "Pedro Trindade Gonçalves Cadilhe Santos (up202205900@up.pt)" << endl;
    cout << string(2*(LINE_SIZE_/5), ' ');
    cout << "Rodrigo Dias Ferreira Loureiro de Sousa (up202205751@up.pt)" << endl;
    cout << "Date: May 2024" << endl;
}
