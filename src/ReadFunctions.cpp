#include "../include/ReadFunctions.h"

/**
 * @brief Function that reads all the Reservoirs information in the selected data folder, allowing for the creation of the nodes of its type, and the population of the graph.
 * @details Complexity
 */

Graph<Node> ReadFunctions::readToy(int i) {
    cout << string(LINE_SIZE_, '-') << endl;
    cout << "Loading data contents..." << endl;
    cout << string(LINE_SIZE_, '-') << endl;

    vector<Node> nodes_toy;
    Graph<Node> g;
    if (i>2 || i<0) { cout << "Error: Toy csv number doesn't exist."; return g;}

    string path = "../csv/toy/";
    switch(i) {
        case 0:
            path = path+"shipping.csv";
            break;
        case 1:
            path = path+"stadiums.csv";
            break;
        case 2:
            path = path+"tourism.csv";
            break;
    }

    ifstream file(path);
    if (!file.is_open()) {cerr << "Error (204): Wrong Path"; return g;}
    string fLine;
    getline(file, fLine);

    if(i==0 or i==1) {
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string id1, id2, distance;
            if (getline(ss, id1, ',') && getline(ss, id2, ',') && getline(ss, distance, ',')) {
                Node a(stoi(id1), "N/A", {0.0,0.0});
                Node z(stoi(id2), "N/A", {0.0,0.0});
                if (g.findVertex(a)==nullptr){g.addVertex(a); a.print();}
                if (g.findVertex(z)==nullptr){g.addVertex(z); z.print();}
                double d = stod(distance);
                g.addEdge(a,z,d);
            }

        }

    }
    else {
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string id1, id2, distance, label1, label2;
            if (getline(ss, id1, ',') && getline(ss, id2, ',') && getline(ss, distance, ',') && getline(ss, label1, ',') && getline(ss, label2, ',')) {
                Node a(stoi(id1), label1, {0.0,0.0});
                Node z(stoi(id2), label2, {0.0,0.0});
                if (g.findVertex(a)==nullptr){g.addVertex(a); a.print();}
                if (g.findVertex(z)==nullptr){g.addVertex(z); z.print();}
                double d = stod(distance);
                g.addEdge(a,z,d);
            }

        }
    }

    return g;
}
Graph<Node> ReadFunctions::readExtra(int i) {
    cout << string(LINE_SIZE_, '-') << endl;
    cout << "Loading data contents..." << endl;
    cout << string(LINE_SIZE_, '-') << endl;

    vector<Node> nodes_extra;
    Graph<Node> g;
    if (i != 25 && i != 50 && i != 75 && i != 100 && i != 200 && i != 300 && i != 400 && i != 500 && i != 600 && i != 700 && i != 800 && i != 900) { cout << "Error: Extra csv number doesn't exist."; return g;}

    string path = "../csv/extra/edges_" + to_string(i) + ".csv";
    string nodepath = "../csv/extra/nodes.csv";


    ifstream file(nodepath);
    if (!file.is_open()) {cerr << "Error (204): Wrong Path"; return g;}
    string fLine;
    getline(file, fLine);

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string id1, lon, lat;
        if (getline(ss, id1, ',') && getline(ss, lon, ',') && getline(ss, lat, ',')) {
            pair<double, double> coordinates = {stod(lon),stod(lat)};
            Node a(stoi(id1),"N/A",coordinates);
            if (g.findVertex(a)==nullptr){g.addVertex(a); a.print();}
        }
    }


    ifstream file2(path);
    if (!file2.is_open()) {cerr << "Error (204): Wrong Path"; return g;}
    string fLine2;
    getline(file, fLine2);


    string line2;
    while (getline(file2, line2)) {
        istringstream ss(line2);
        string id1, id2, distance;
        if (getline(ss, id1, ',') && getline(ss, id2, ',') && getline(ss, distance, ',')) {

            Node a(stoi(id1),"N/A", {0.0,0.0});
            Node z(stoi(id2), "N/A", {0.0,0.0});
            g.addEdge(g.findVertex(a)->getInfo(), g.findVertex(z)->getInfo(), stod(distance));
        }
    }

    return g;
}

/*
vector<Node> ReadFunctions::readReservoirs(string const &pathname) {
    vector<Node> nodesReservoirs;

    ifstream file(pathname);
    if (!file.is_open()) {
        cerr << "Error (204): Wrong Path";
        return nodesReservoirs;
    }
    string fLine;
    getline(file, fLine);

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string reservoir, municipality, code, id, maximumDelivery;


        if (getline(ss, reservoir, ',') && getline(ss, municipality, ',') 
			&& getline(ss, id, ',') && getline(ss, code, ',') && getline(ss, maximumDelivery, ',')) {
            nodesReservoirs.push_back(Node('s', reservoir, stoi(id), code, municipality, stoi(maximumDelivery), 0));
        } else {
            cerr << "Error (302): Reservoir Loading Error";
        }
    }

    file.close();
    return nodesReservoirs;
}


vector<Node> ReadFunctions::readCities(unordered_map<string, string> &cityDict, string const &pathname) {
    vector<Node> nodesCities;

    ifstream file(pathname);
    if (!file.is_open()) {
        cerr << "Error (205): Wrong Path";
        return nodesCities;
    }
    string fLine;
    getline(file, fLine);

    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        string city, code, id, population, demand;

        if (getline(ss, city, ',') && getline(ss, id, ',') && getline(ss, code, ',') 
			&& getline(ss, demand, ',') && getline(ss, population, ',')) {
            nodesCities.push_back(Node('t', Node::removeCarriageReturn(city), stoi(id), code,"", stoi(population), stod(demand)));
            cityDict[Node::removeCarriageReturn(city)] = Node::removeCarriageReturn(code);
        } else {
            cerr << "Error (301): City Loading Error";
        }
    }
    if (cityDict.empty()) {
        cerr << "Error (701): Map Empty!";
    }

    file.close();
    return nodesCities;
}


vector<Node> ReadFunctions::readStations(string const &pathname) {
    vector<Node> nodesStations;

    ifstream file(pathname);
    if (!file.is_open()) {
        cerr << "Error (206): Wrong Path";
        return nodesStations;
    }
    string fLine;
    getline(file, fLine);

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string id, code;
        if (getline(ss, id, ',') && getline(ss, code, ',')) {
            nodesStations.push_back(Node('u', "", stoi(id), code, "", 0, 0));
        } else {
            cerr << "Error (303): Station Loading Error";
        }
    }
    file.close();
    return nodesStations;
}


void ReadFunctions::readPipes(Graph<Node> &graph, std::string const &pathname) {
    ifstream file(pathname);
    if (!file.is_open()) {
        cerr << "Error (207): Wrong Path";
        return;
    }
    string fLine;
    getline(file, fLine);

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string start, end, capacity, direction;
        if (getline(ss, start, ',') && getline(ss, end, ',') && getline(ss, capacity, ',') && getline(ss, direction, ',')) {
            Node a('d', "", 0, start, "", 0, 0);
            Node b('d', "", 0, end, "", 0, 0);

            auto vertexA = graph.findVertex(a);
            auto vertexB = graph.findVertex(b);

            if (vertexA && vertexB) {
                graph.addEdge(vertexA->getInfo(), vertexB->getInfo(), stoi(capacity));

                int d = stoi(direction);
                if (d == 0) {
                    graph.addEdge(vertexB->getInfo(), vertexA->getInfo(), stoi(capacity));
                }
            } else {
                cerr << "Error (501): Vertex not found in the graph" << endl;
            }
        } else {
            cerr << "Error (304): Pipe Loading Error";
        }
    }
    file.close();
}
*/

