
#ifndef YARAOSUD_NODE_H
#define YARAOSUD_NODE_H

#include "Include.h"

class Node {
    private:
        int index_; //number of the index of the node
        string info_; //info related to the node (such as the labels in tourism.csv)
        pair<double,double> coordinates_;


    public:
        /**
        * @brief Constructor of the Node. The type of the Node depends on the values of its atributes.
        */
        Node(int index, string info, pair<double,double> coordinates) {
            index_=index;
            info_=info;
            coordinates_=coordinates;
        }

        //Destructor
        ~Node() {}

        //Getters
        int getIndex() {return index_;}
        string getInfo() {return info_;}
        pair<double,double> getCoordinates() {return coordinates_;}

        //Operator
        bool operator==(const Node& node) {
            return (index_ == node.index_);
        }

        /**
        * @brief Function that prints the information of the various types of Nodes that are being made according to the chosen data folder.
        */
        void print() {
            cout << "Index: " << index_ << "   Info: " << info_ << "   Coordinates: " << coordinates_.first << "," << coordinates_.second << endl;
            cout << string(LINE_SIZE_, '-') << endl;
        }

        //Util
        static string stringToHex(const std::string& input) {
            std::stringstream hexStream;
            hexStream << hex << uppercase << setfill('0');

            for (char ch : input) {
                hexStream << setw(2) << static_cast<int>(static_cast<unsigned char>(ch));
            }

            return hexStream.str();
        }
        static string removeCarriageReturn(const string& input) {
            size_t lastNonCR = input.find_last_not_of('\r');

            if (lastNonCR != string::npos) {
                return input.substr(0, lastNonCR + 1);
            } else {
                // String consists only of carriage returns, return an empty string
                return "";
            }
        }
        
};




#endif //YARAOSUD_NODE_H