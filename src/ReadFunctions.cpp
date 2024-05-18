#include "../include/ReadFunctions.h"

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
                g.addEdge(z,a,d);
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
                if (g.findVertex(a)==nullptr){g.addVertex(a);}
                if (g.findVertex(z)==nullptr){g.addVertex(z);}
                double d = stod(distance);
                g.addEdge(a,z,d);
                g.addEdge(z,a,d);
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

            g.addEdge(g.findVertex(z)->getInfo(), g.findVertex(a)->getInfo(), stod(distance));
        }
    }

    return g;
}


Graph<Node> ReadFunctions::readReal(int i) {
    cout << string(LINE_SIZE_, '-') << endl;
    cout << "Loading data contents..." << endl;
    cout << string(LINE_SIZE_, '-') << endl;

    vector<Node> nodes_real;
    Graph<Node> g;
    if (i < 1 && i > 3) { cout << "Error: Real Graph number doesn't exist."; return g;}

    string path = "../csv/real/graph" + to_string(i) + "/";
    string nodepath = path + "nodes.csv";
    string edgepath = path + "edges.csv";


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


    ifstream file2(edgepath);
    if (!file2.is_open()) {cerr << "Error (204): Wrong Path"; return g;}
    string fLine2;
    getline(file2, fLine2);


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