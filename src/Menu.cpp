#include "../include/Menu.h"
void waitForInput() {
    string input;
    getline(std::cin, input); // Wait for user to press Enter
}
/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that runs the first menu of the app (selection of the source of the data to be used), and later the main menu (with all the possible operations).
 * */
void Menu::run() {
    // Graph
    graph = Graph<Node>();
    vector<Node> nodeS;
    vector<Node> nodeT;
    vector<Node> nodeU;

    // Load Graph
    while (true) {
        string decision;
        string path;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Welcome to the Water Supply Management Analysis Tool!" << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Select your data folder:" << endl;
        cout << "1 - Madeira." << endl;
        cout << "2 - Mainland Portugal." << endl;
        cout << "3 - Custom." << endl;
        cout << "0 - Exit." << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Please select the task you wish to perform by inputting its number: ";

        while (true) {
            getline(cin, decision);
            cout << endl;
            if (decision.size() != 1) { cout << "Invalid input. Please enter a number between 1 and 4: "; continue;}
            switch (decision[0]) {
                case '1':
                    path = "../csv/Madeira/";
                    goto load;
                case '2':
                    path = "../csv/Mainland Portugal/";
                    goto load;
                case '3':
                    cout << "Please enter the path to the folder containing the csv files: ";
                    getline(cin, path);
                    goto load;
                case '0':
                    cout << "Goodbye!" << endl;
                    exit(0);
                default:
                    cout << "Invalid input. Please enter a number between 1 and 4: ";
                    break;
            }
        }
        load:
        nodeS = ReadFunctions::readReservoirs(path + "Reservoirs.csv");
        nodeT = ReadFunctions::readCities(cityDict, path + "Cities.csv");
        nodeU = ReadFunctions::readStations(path + "Stations.csv");
        for (const Node &i : nodeS) {
            graph.addVertex(i);
        }
        for (const Node &i : nodeT) {
            graph.addVertex(i);
        }
        for (const Node &i : nodeU) {
            graph.addVertex(i);
        }
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Loading data contents..." << endl;
        cout << string(LINE_SIZE_, '-') << endl;

        for (auto n : graph.getVertexSet()) {
            n->getInfo().print();
        }
        cout << "Loading system..." << endl;
        ReadFunctions::readPipes(graph, path + "Pipes.csv");
        break;
    }
    //Real Menu
    while (true) {
        string decision;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Select your operation:" << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "1 - Maximum amount of reachable water of a given city." << endl; //T2.1
        cout << "2 - List of maximum amount of reachable water per city." << endl; //T2.1
        cout << "3 - Water reservoirs supply and demand status." << endl; //T2.2
        cout << "4 - Analytics of Capacity and Flow." << endl; //T2.3
        cout << "5 - Water reservoirs deactivation analysis." << endl; //T3.1
        cout << "6 - Pumping stations deactivation analysis." << endl; //T3.2
        cout << "7 - Affected cities by given pipe analysis." << endl; //T3.3
        cout << "8 - Critical pipes by given city analysis." << endl; //T3.3
        cout << "9 - Credits." << endl;
        cout << "0 - Exit." << endl;
        cout << string(LINE_SIZE_, '-') << endl;
        cout << "Please select the task you wish to perform by inputting its number: ";
        getline(cin, decision);
        cout << string(LINE_SIZE_, '-') << endl;
        cout << endl;
        if (decision.size() != 1) {
            cout << "Invalid input. Please enter a number between 0 and 9: " << endl;
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
            case '5':
                case5();
                waitForInput();
                break;
            case '6':
                case6();
                waitForInput();
                break;
            case '7':
                case7();
                waitForInput();
                break;
            case '8':
                case8();
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
                cout << "Invalid input. Please enter a number between 0 and 9: " << endl;
                break;
        }
    }
}


void Menu::case1() {
    string city;
    cout << "Please insert the name of the city: ";
    getline(cin,city);
    Node a('d', "", 0, (cityDict[city]), "", 0, 0);
    cout << string(LINE_SIZE_, '-') << endl;
    cout << "Maximum amount of reachable water in " << city << " is " << OperationFunctions::maxFlowOfCity(graph, a) << endl;
}

void Menu::case2() {
    double max = OperationFunctions::maxFlowPerCity(graph);

    cout << string(LINE_SIZE_, '-') << endl;
    cout << "Total flow: " << max << endl;
}

void Menu::case3() {
    vector<pair<Node, double>> res = OperationFunctions::supplyAndDemand(graph);
    
    if (res.empty()) {
        cout << "All cities are supplied!";
    }
    else {
        cout << "The cities that cannot be supplied by the desired water rate level are listed bellow, with the amount of water flow in deficit." << endl;
        for (auto t : res) {
            cout << t.first.getName() << " (" << t.first.getCode() << ") --> " << t.second << endl;
        }
    }
}

void Menu::case4() {
    pair<double,double> averageAndMax;
    double variances = OperationFunctions::variance(graph);
    averageAndMax=OperationFunctions::averageAndMaxOfDifferenceOfCapAndFlow(graph);

    cout << "Average of the differences between Capacities and Flows in all pipelines: " << averageAndMax.first << endl;
    cout << "Maximum difference between Capacity and Flow, out of all pipelines: " << averageAndMax.second << endl;
    cout << "Variance of the differences between Capacities and Flows in all pipelines: " << variances << endl;
}

void Menu::case5() {
    string reservoirCode;
    cout << "Please insert the code of the Reservoir to be removed: ";
    getline(cin,reservoirCode);
    Node del('d', "", 0, reservoirCode, "", 0, 0);
    cout << string(LINE_SIZE_, '-') << endl;
    OperationFunctions::deactivation(graph, del);

}

void Menu::case6() {
    string pumpingCode;
    cout << "Please insert the code of the Pumping Station to be removed: ";
    getline(cin, pumpingCode);
    Node del('u', "", 0, pumpingCode, "", 0, 0);
    cout << string(LINE_SIZE_, '-') << endl;
    OperationFunctions::deactivation(graph, del);
}

void Menu::case7() {
    string A, B;
    char charA, charB;
    cout << "Please insert the Service Point A of the Pipe to be removed: ";
    getline(cin, A);
    if (A[0] == 'R') {
        charA = 's';
    }
    else if (A[0] == 'P') {
        charA = 'u';
    }
    else {
        charA = 't';
    }
    cout << "Please insert the Service Point B of the Pipe to be removed: ";
    getline(cin, B);
    if (B[0] == 'R') {
        charB = 's';
    }
    else if (A[0] == 'P') {
        charB = 'u';
    }
    else {
        charB = 't';
    }
    Node start(charA,"", 0, A, "", 0, 0);
    Node end(charB, "", 0, B, "", 0, 0);
    cout << string(LINE_SIZE_, '-') << endl;
    OperationFunctions::citiesOfCriticalPipe(graph, start, end);
}

void Menu::case8() {
    string city;
    cout <<  "Please insert the City you want to examine: ";
    getline(cin, city);
    Node a('t', "", 0, cityDict[city], "", 0, 0);
    cout << string(LINE_SIZE_, '-') << endl;
    OperationFunctions::criticalPipesOfCity(graph,a);
}

void Menu::case9() {
    cout << "This program was created by:" << endl;
    cout << string(2*(LINE_SIZE_/5), ' ');
    cout << "Afonso Pedro Maia de Castro (up202208026@up.pt)" << endl;
    cout << string(2*(LINE_SIZE_/5), ' ');
    cout << "Pedro Trindade Gonçalves Cadilhe Santos (up202205900@up.pt)" << endl;
    cout << string(2*(LINE_SIZE_/5), ' ');
    cout << "Rodrigo Dias Ferreira Loureiro de Sousa (up202205751@up.pt)" << endl;
    cout << "Date: March 2024" << endl;
}


