#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

#include "Gate.h"
#include "Fault.h"

#define DEBUG 0
#define D 2
#define DBAR 3
#define X 4
using namespace std;



void printNetMap(map<int, vector<int>> &m)
{
    cout << "=== NET MAP ===" << endl;
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        cout << "KEY: " << itr->first << "\tVALUES: ";
        for (auto &vit : itr->second)
        {
            cout << vit << " ";
        }
        cout << endl;
    }
    cout << "=== END NET MAP ===" << endl;
}

void printNetVals(map<int, int> &m)
{
    cout << "===== NET VALUES ======" << endl;
    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        cout << "NET: " << itr->first << "\tVAL: " << itr->second << endl;
    }
    cout << "=======================" << endl;
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
void updateMaps(string gate_entry, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, int key, vector<int> &inputs, vector<int> &outputs, map<int, int> &net_driver)
{
    string gate_name;
    string in1, in2, out;
    istringstream iss(gate_entry);
    iss >> gate_name;
    if (gate_name == "INV") {
        iss >> in1 >> out;
        int iin1 = stoi(in1); 
        int iin2 = stoi(in1);
        int iout = stoi(out);

        // update maps for INV
        gate_map.insert(make_pair(key, new INVGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "BUF") {
        iss >> in1 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in1);
        int iout = stoi(out);

        // update maps for BUF
        gate_map.insert(make_pair(key, new BUFGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "AND") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        
        // update maps for AND
        gate_map.insert(make_pair(key, new ANDGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "NAND") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);

        // update maps for NAND
        gate_map.insert(make_pair(key, new NANDGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "OR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        
        // update maps for OR
        gate_map.insert(make_pair(key, new ORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "NOR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);

        // update maps for NOR
        gate_map.insert(make_pair(key, new NORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "XOR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);

        // update maps for XOR
        gate_map.insert(make_pair(key, new XORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "XNOR") {
        iss >> in1 >> in2 >> out;
        int iin1 = stoi(in1);
        int iin2 = stoi(in2);
        int iout = stoi(out);
        
        // update maps for XNOR
        gate_map.insert(make_pair(key, new XNORGate(iin1, iin2, iout))); 
        updateNetMap(net_map, iin1, key);
        updateNetMap(net_map, iin2, key);
        net_driver.insert(make_pair(iout, key));

    } else if (gate_name == "INPUT") {
        string next;
        int ii;
        while (iss >> next) {
            ii = stoi(next);
            if (ii != -1) {
                inputs.push_back(ii);
                net_driver.insert(make_pair(ii, -1));
            }
        }
    } else if (gate_name == "OUTPUT") {
        string next;
        int ii;
        while (iss >> next) {
            ii = stoi(next);
            if (ii != -1) {
                outputs.push_back(ii);
            }
        }
    } 
    /*
    else {
        cout << "====== TYPE DOES NOT EXIST ========" << endl;
        cout << gate_name << endl;
    } 
    */
}


void updateFaultVec(vector<fault> &fault_vec, int net, int sa_val)
{
    fault temp;
    temp.sa = sa_val;
    temp.net = net;
    // make sure fault is not already in list
    bool exists = false;
    for (auto &v : fault_vec) 
    {
        if (compareFaults(v, temp)) {
            exists = true;
            break;
        }
    }

    // if does not exist in list already, add it
    if (!exists)
        fault_vec.push_back(temp);
}

// use command line arg to parse input file representing circuit line by line 
void parseNetlistFile(const char filename[], map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, vector<int> &inputs, vector<int> &outputs, map<int, int> &net_driver)
{
    ifstream netlist(filename);
    string line;
    int key = 0;
    while (getline(netlist, line))
    {
        // for each gate in the circuit, update the maps
        updateMaps(line, net_map, gate_map, key, inputs, outputs, net_driver);
        key++;
    }
}
   
struct NetValue {
    int net;
    int val;
};
 
void resetValueMap(map<int, int> &m)
{
    for (auto itr = m.begin(); itr != m.end(); ++itr) 
    {
        itr->second = X;
    }
}


NetValue backtrace(int net, int val, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, map<int, int> &net_driver, map<int, int> &value_map)
{
    cout << "BACKTRACING net: " << net << ", w val: " << val << endl;
    NetValue n;
    int cur_gate = net_driver[net];
    int i;
    int v = val;
    int temp;
    while (cur_gate != -1)
    {
        i = gate_map[cur_gate]->getParity();
        v = (v + i) % 2;
        cout << "gate: " << cur_gate << "; parity: " << i << ", v: " << v << endl;
        // get net of input1. check if value is 'x' 
        temp = gate_map[cur_gate]->getNet1(); 
        if (value_map[temp] == X) {
            n.net = temp; 
        } else {
            temp = gate_map[cur_gate]->getNet2();
            if (value_map[temp] == X) {
                n.net = temp;
            } else {
                cout << "neither input is x!" << endl;
                break;
            }
        } 
        cur_gate = net_driver[n.net];
        cout << "next gate: " << cur_gate << endl;
    }    
    n.val = v;
    return n;
} 

// return 1 if detected
// 0 otherwise
int imply(int net, int val, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, map<int, int> &value_map, vector<int> &input_vec, vector<int> &output_vec, vector<int> &D_frontier)
{
    cout << "IMPLY" << endl;
    // update input value for all affected gates
    value_map[net] = val; 
    // add gates affected by input to queue and update inputs
    queue<int> q;
    for (auto &gate : net_map[net]) {
        q.push(gate);
        gate_map[gate]->setInput(val, net);
    }

    cout << "QUEUE" << endl;
    printQueue(q);
    
    // evaluate gates in queue and update value map
    int g, out_net, n_val;
    while(!q.empty())
    {

        g = q.front();
        cout << "EVALUATING GATE: " << g << endl;
        cout << "EVAL RESULT: " << gate_map[g]->evaluate() << endl;
        out_net = gate_map[g]->getNetout();
        n_val = gate_map[g]->getOut();
        value_map[out_net] = n_val;
        
        // add new gates to queue using net map
        for (auto &new_gate : net_map[out_net])
            q.push(new_gate);

        cout << "====== NEW VALUE MAP =========" << endl;
        printNetVals(value_map);
        q.pop();
    }
    return 1;
}

NetValue objective(int net, int val, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, map<int, int> &net_driver, map<int, int> &value_map, vector<int> &D_frontier)
{
    NetValue n; 
    if (value_map[net] == X) {
        cout << "objective x" << endl;
        n.net = net;
        n.val = (val) ? 0 : 1; 
        return n;
    }


    int cur_gate = D_frontier.back();
    int temp = gate_map[cur_gate]->getNet1(); 
    if (value_map[temp] == X) {
        n.net = temp; 
    } else {
        temp = gate_map[cur_gate]->getNet2();
        if (value_map[temp] == X) {
            n.net = temp;
        } else {
            cout << "neither input is x!" << endl;
        }
    } 
    n.val = (gate_map[cur_gate]->getControlling()) ? 0 : 1;
    cout << "OBJECTIVE: " << n.net << " " << n.val << endl;
    return n;    
}


int main(int argc, char** argv)
{
    if (argc != 4) {
        cout << "WRONG NUMBER OF INPUTS" << endl;
        return -1;
    }
    const char *filename = argv[1];
    int faulty_net = stoi(argv[2]);
    int faulty_val = stoi(argv[3]);
    cout << faulty_net << " FAULTY NET: " << endl;
    //const char *faulty_val = argv[3];

    // variable init
    map<int, vector<int>> net_map;
    map<int, Gate*> gate_map;
    vector<int> in_vec;
    vector<int> out_vec;
    vector<fault> potential_fault_vec;
    map<int, vector<fault>> detected_fault_map;
    map<int, int> net_driver;
    map<int, int> value_map;
    vector<int> D_frontier;

    parseNetlistFile(filename, net_map, gate_map, in_vec, out_vec, net_driver);
    // assign all nets to x
    for (auto itr = net_map.begin(); itr != net_map.end(); ++itr) 
    {
        value_map.insert(make_pair(itr->first, X));
    }
    for (auto &v : out_vec)
    {
        auto itr = value_map.find(v);
        if (itr == value_map.end())
            value_map.insert(make_pair(v, X));
    }
    
    cout << "NET MAP" << endl;
    printNetMap(net_map);
    cout << "VALUE MAP" << endl;
    printNetVals(value_map);

    NetValue objective_pair = objective(faulty_net, faulty_val, net_map, gate_map, net_driver, value_map, D_frontier);
    NetValue backtrace_pair = backtrace(objective_pair.net, objective_pair.val, net_map, gate_map, net_driver, value_map);
    cout << "net: " << backtrace_pair.net << ", val: " << backtrace_pair.val << endl;
    imply(backtrace_pair.net, backtrace_pair.val, net_map, gate_map, value_map, in_vec, out_vec, D_frontier);

   
    //if(DEBUG) {printNetMap(net_map);}
    int N = in_vec.size();
    int M = out_vec.size() + 1;
    char output[M];

    // PODEM
    return 0;
}
