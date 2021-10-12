#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>

#include "Gate.h"

using namespace std;

void printNetMap(map<int, vector<int>> &m)
{
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        cout << "KEY: " << itr->first << "\tVALUES: ";
        for (auto &vit : itr->second)
        {
            cout << vit << " ";
        }
        cout << endl;
    }
}

void printQueue(queue<int> q)
{
    while(!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void updateNetMap(map<int, vector<int>> &net_map, int net_key, int gate_key)
{
    auto itr = net_map.find(net_key);
    if (itr != net_map.end())
        net_map[net_key].push_back(gate_key);
    else
        net_map.insert(make_pair(net_key, vector<int> {gate_key}));
}

// use entries for gates to update maps for nets and gates
void updateMaps(string gate_entry, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, int key, vector<int> &inputs, vector<int> &outputs)
{
    string gate_name;
    string in1, in2, out;
    istringstream iss(gate_entry);
    iss >> gate_name;
    cout << "========================================" << endl;
    if (gate_name == "INV") {
        iss >> in1 >> out;
        int iin1 = stoi(in1); 
        int iin2 = stoi(in1);
        int iout = stoi(out);
        cout << "INV - " << "in: " << in1 << ", out: " << out << endl;

        // update maps for INV
        gate_map.insert(make_pair(key, new INVGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);

    } else if (gate_name == "BUF") {
        iss >> in1 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in1);
        int iout = stoi(out);
        cout << "BUF - " << "in: " << in1 << ", " << in2 << ", out: " << out << endl;

        // update maps for BUF
        gate_map.insert(make_pair(key, new BUFGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);

    } else if (gate_name == "AND") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        cout << "AND - " << "in: " << in1 << ", " << in2 <<  ", out: " << out << endl;
        
        // update maps for AND
        gate_map.insert(make_pair(key, new ANDGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);

    } else if (gate_name == "NAND") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        cout << "NAND - " << "in: " << in1 << ", " << in2 << ", out: " << out << endl;

        // update maps for NAND
        gate_map.insert(make_pair(key, new NANDGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);

    } else if (gate_name == "OR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        cout << "OR - " << "in: " << in1 << ", " << in2 << ", out: " << out << endl;
        
        // update maps for OR
        gate_map.insert(make_pair(key, new ORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);

    } else if (gate_name == "NOR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        cout << "NOR - " << "in: " << in1 << ", " << in2 << ", out: " << out << endl;

        // update maps for NOR
        gate_map.insert(make_pair(key, new NORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);

    } else if (gate_name == "XOR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        cout << "XOR - " << "in: " << in1 << ", " << in2 << ", out: " << out << endl;

        // update maps for XOR
        gate_map.insert(make_pair(key, new XORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);

    } else if (gate_name == "XNOR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        cout << "XNOR - " << "in: " << in1 << ", " << in2 << ", out: " << out << endl;
        
        // update maps for XNOR
        gate_map.insert(make_pair(key, new XNORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);

    } else if (gate_name == "INPUT") {
        cout << "INPUTS: " << endl;
        string next;
        int ii;
        while (iss >> next) {
            ii = stoi(next);
            if (ii != -1) {
                inputs.push_back(ii);
                cout << next << " ";
            }
        }
        cout << endl;
    } else if (gate_name == "OUTPUT") {
        cout << "OUTPUTS:" << endl;
        string next;
        int ii;
        while (iss >> next) {
            ii = stoi(next);
            if (ii != -1) {
                outputs.push_back(ii);
                cout << next << " ";
            }
        }
        cout << endl;
    } else {
        cout << "====== TYPE DOES NOT EXIST ========" << endl;
    } 
}


// use command line arg to parse input file representing circuit line by line 
void parseFile(const char filename[], map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, vector<int> &inputs, vector<int> &outputs)
{
    ifstream netlist(filename);
    string line;
    int key = 0;
    while (getline(netlist, line))
    {
        // for each gate in the circuit, update the maps
        updateMaps(line, net_map, gate_map, key, inputs, outputs);
        key++;
    }
}
    
string simulateCircuit(map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, vector<int> &inputs, vector<int> &outputs, const char binary_in[], int N)
{
    // init gate queue
    queue<int> q;
    int k = 0;
    for(auto &vin : inputs)
    {
        auto current_net = net_map.find(vin);
        if (current_net != net_map.end()) 
        {
            // loop through gates for net entry
            for(auto &vgate : net_map[vin])
            {
                gate_map[vgate]->setInput((int) binary_in[k], (int) vin);
                // if all inputs are set for gate
                if(gate_map[vgate]->areInputsSet())
                    q.push(vgate);
            }
        }
        cout << "This is bin[k]: " << binary_in[k] << ", K: " << k << endl;
        ++k;
    }
    /*
    while(!q.empty())
    {
        q.front()

    }
    */
    
    printQueue(q);

    string output = "1010101";
    return output;

}

int main(int argc, char** argv)
{
    const char *filename = argv[1];
    const char *bin_in = argv[2];

    map<int, vector<int>> net_map;
    map<int, Gate*> gate_map;
    vector<int> in_vec;
    vector<int> out_vec;
    parseFile(filename, net_map, gate_map, in_vec, out_vec);
    printNetMap(net_map);
    int N = in_vec.size();
    
    if (N != string(bin_in).length()) {
        cout << "Wrong input size" << endl;
        return -1;
    }

    string output = simulateCircuit(net_map, gate_map, in_vec, out_vec, bin_in, N);
    cout << "========= CIRCUIT OUTPUT: ==========" << endl;
    cout << output << endl;
    return 0;
}
