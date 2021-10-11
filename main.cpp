#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

#include "Gate.h"

using namespace std;

// use entries for gates to update maps for nets and gates
void updateMaps(string gate_entry, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, int key)
{
    string gate_name;
    string in1, in2, out;
    istringstream iss(gate_entry);
    iss >> gate_name;
    cout << gate_name << " : This is in updateMaps" << endl;
    if (gate_name == "INV") {
        gate_map.insert(make_pair(key, new INVGate())); 
        iss >> in1 >> out;
        cout << "MYINV" << "in: " << in1 << ", out: " << out << endl;
    } else if (gate_name == "BUF") {
        gate_map.insert(make_pair(key, new BUFGate())); 
    } else if (gate_name == "AND") {
        gate_map.insert(make_pair(key, new ANDGate())); 
    } else if (gate_name == "NAND") {
        gate_map.insert(make_pair(key, new NANDGate())); 
    } else if (gate_name == "OR") {
        gate_map.insert(make_pair(key, new ORGate())); 
    } else if (gate_name == "NOR") {
        gate_map.insert(make_pair(key, new NORGate())); 
    } else if (gate_name == "XOR") {
        gate_map.insert(make_pair(key, new XORGate())); 
    } else if (gate_name == "XNOR") {
        gate_map.insert(make_pair(key, new XNORGate())); 
    } else if (gate_name == "INPUT") {
        cout << "INPUTS" << endl;
    } else if (gate_name == "OUTPUT") {
        cout << "OUTPUTS:" << endl;
    } 
}


// use command line arg to parse input file representing circuit line by line 
void parseFile(const char filename[], map<int, vector<int>> &net_map, map<int, Gate*> &gate_map)
{
    ifstream netlist(filename);
    string line;
    int key = 0;
    while (getline(netlist, line))
    {
        // for each gate in the circuit, update the maps
        updateMaps(line, net_map, gate_map, key);
        key++;
    }
}
    

int main(int argc, char** argv)
{
    map<int, vector<int>> net_map;
    map<int, Gate*> gate_map;
    const char *filename = argv[1];
    parseFile(filename, net_map, gate_map);

    return 0;
}
