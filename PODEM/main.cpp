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

#define SUCCESS 1
#define FAIL 0
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

void printVector(vector<int> v)
{
    for (auto &e : v)
        cout << e << " ";

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

void addDFrontier(int net, vector<int> &D_frontier)
{
    bool exists = false;
    for (auto &d : D_frontier)
    {
        if (d == net) 
        {
            exists = true;
            break;
        }
    }
    if ( !exists )
        D_frontier.push_back(net);
}

void updateDFrontier(map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, map<int, int> &value_map, vector<int> &D_frontier)
{
    for (auto itr = value_map.begin(); itr != value_map.end(); ++itr)
    {
        if (itr->second == D || itr->second == DBAR)
        {
            // value could be on the D Frontier
            for (auto &gate : net_map[itr->first])
            {
                if (gate_map[gate]->getOut() == X)
                {
                    addDFrontier(gate, D_frontier);
                }
            }
        }
    }
}



NetValue backtrace(int net, int val, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, map<int, int> &net_driver, map<int, int> &value_map)
{
    //cout << "BACKTRACING net: " << net << ", w val: " << val << endl;
    NetValue n;
    int cur_gate = net_driver[net];
    // check if it is already PI
    if (cur_gate < 0)
    {
        n.net = net;
        n.val = val;
        return n;
    }
    int i;
    int v = val;
    int temp;
    while (cur_gate != -1)
    {
        i = gate_map[cur_gate]->getParity();
        v = (v + i) % 2;
        //cout << "gate: " << cur_gate << "; parity: " << i << ", v: " << v << endl;
        // get net of input1. check if value is 'x' 
        temp = gate_map[cur_gate]->getNet1(); 
        if (value_map[temp] == X) {
            n.net = temp; 
        } else {
            temp = gate_map[cur_gate]->getNet2();
            if (value_map[temp] == X) {
                n.net = temp;
            } else {
                //cout << "neither input is x! (backtrace)" << endl;
                break;
            }
        } 
        cur_gate = net_driver[n.net];
        //cout << "next gate: " << cur_gate << endl;
    }    
    n.val = v;
    return n;
} 

// return 1 if detected
// 0 otherwise
int imply(int fnet, int fval, int net, int val, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, map<int, int> &value_map, vector<int> &input_vec, vector<int> &output_vec, vector<int> &D_frontier)
{
    // update input value for all affected gates
    if (fnet == net)
    {
        if (val == 0 && fval == 1)
            val = DBAR;
        if (val == 1 && fval == 0)
            val = D;
    }
    value_map[net] = val; 

    // add gates affected by input to queue and update inputs
    queue<int> q;
    for (auto &gate : net_map[net]) {
        q.push(gate);
        gate_map[gate]->setInput(val, net);
    }

    //cout << "QUEUE" << endl;
    //printQueue(q);
    
    // evaluate gates in queue and update value map
    int g, out_net, n_val;
    while(!q.empty())
    {

        g = q.front();
        //cout << "EVALUATING GATE: " << g << ". OUT NET: " << gate_map[g]->getNetout() << endl;
        //cout << "EVAL RESULT: " << gate_map[g]->evaluate() << endl;
        out_net = gate_map[g]->getNetout();
        gate_map[g]->evaluate();
        n_val = gate_map[g]->getOut();
        if (fnet == out_net)
        {
            if (n_val == 0 && fval == 1)
                n_val = DBAR;
            if (n_val == 1 && fval == 0)
                n_val = D;

            gate_map[g]->overrideOut(n_val);
        }
        value_map[out_net] = n_val;
        
        // add new gates to queue using net map
        for (auto &new_gate : net_map[out_net])
        {
            gate_map[new_gate]->setInput(n_val, out_net);
            q.push(new_gate);
        }

        //cout << "====== NEW VALUE MAP =========" << endl;
        //printNetVals(value_map);
        q.pop();
    }
    updateDFrontier(net_map, gate_map, value_map, D_frontier);
    return 1;
}

NetValue objective(int net, int val, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, map<int, int> &net_driver, map<int, int> &value_map, vector<int> &D_frontier)
{
    NetValue n; 
    if (value_map[net] == X) {
        //cout << "objective x" << endl;
        n.net = net;
        n.val = (val) ? 0 : 1; 
        return n;
    }


    int cur_gate = D_frontier.back();
    D_frontier.pop_back();
    int temp = gate_map[cur_gate]->getNet1(); 
    if (value_map[temp] == X) {
        n.net = temp; 
    } else {
        temp = gate_map[cur_gate]->getNet2();
        if (value_map[temp] == X) {
            n.net = temp;
        } else {
            if (DEBUG) {cout << "neither input is x!" << endl;}
        }
    } 
    n.val = (gate_map[cur_gate]->getControlling()) ? 0 : 1;
    if (DEBUG) {cout << "OBJECTIVE: " << n.net << " " << n.val << endl;}
    return n;    
}

int traceXPath(int net, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, vector<int> &out_vec, map<int, int> &value_map)
{
    int netout, out;
    for (auto &gate : net_map[net])
    {
        netout = gate_map[gate]->getNetout();
        out = gate_map[gate]->getOut();
        if (out != X)
            return FAIL;

        if (find(out_vec.begin(), out_vec.end(), netout) == out_vec.end())
        {
            if (out == X)
                return SUCCESS;
            else
                return FAIL;
        }
        
        if (traceXPath(netout, net_map, gate_map, out_vec, value_map) == FAIL)
            continue; 

        return SUCCESS;
    }
    return FAIL;
}

int xPathCheck(map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, vector<int> &out_vec, map<int, int> &value_map, vector<int> &D_frontier)
{
    int net, out, gate;
    bool flag;
    for (auto &d : D_frontier)
    {
        net = gate_map[d]->getNetout();
        
        if (traceXPath(net, net_map, gate_map, out_vec, value_map) == SUCCESS)
            return SUCCESS;
    }
    return FAIL;
}

int podem(int net, int val, map<int, vector<int>> &net_map, map<int, Gate*> &gate_map, vector<int> &in_vec, vector<int> &out_vec, map<int, int> &net_driver, map<int, int> &value_map, vector<int> &D_frontier, int stack_level)
{
    if (DEBUG) {cout << "====== STACK LEVEL : " << stack_level << endl;}
    // check for error at PO
    for (auto &o : out_vec)
    {
        if ((value_map[o] == D) || (value_map[o] == DBAR))
            return SUCCESS;
    }
   
    // check if test is possible
    if (value_map[net] == val) {
        if (DEBUG) {cout << "FAIL...value map == val" << endl;}
        return FAIL;
    }
    
    //printVector(D_frontier);
    if (D_frontier.size() == 0) {
        if (value_map[net] != X) {
            if (DEBUG) {cout << "FAIL...D frontier empty & net != X" << endl;}
            return FAIL;
        }
    } else if (xPathCheck(net_map, gate_map, out_vec, value_map, D_frontier) == FAIL) {
        if (DEBUG) {cout << "FAIL...X path check" << endl;}
        return FAIL;
    }


    // objective
    NetValue objective_pair = objective(net, val, net_map, gate_map, net_driver, value_map, D_frontier);
    if (DEBUG) {cout << "----- OBJ done. net: " << objective_pair.net << ".val: " << objective_pair.val << endl;}
    // backtrace
    NetValue backtrace_pair = backtrace(objective_pair.net, objective_pair.val, net_map, gate_map, net_driver, value_map);
    if (DEBUG) {cout << "----- BACKTRACE done. net: " << backtrace_pair.net << ", val: " << backtrace_pair.val << endl;}
    // imply
    imply(net, val, backtrace_pair.net, backtrace_pair.val, net_map, gate_map, value_map, in_vec, out_vec, D_frontier);
    if (DEBUG) {cout << "----- IMPLY done. value map: " << endl;}
    //printNetVals(value_map);

    if (DEBUG) {
        cout << "----- D Frontier updated: " << endl;
        printVector(D_frontier);
    }

    // check for PODEM success
    if ( podem(net, val, net_map, gate_map, in_vec, out_vec, net_driver, value_map, D_frontier, stack_level+1) == SUCCESS )
        return SUCCESS;

    // reverse decision
    //cout << "============= REVERSE DECISION ====================" << endl;
    imply(net, val, backtrace_pair.net, (backtrace_pair.val) ? 0 : 1, net_map, gate_map, value_map, in_vec, out_vec, D_frontier);
    // check for success
    if ( podem(net, val, net_map, gate_map, in_vec, out_vec, net_driver, value_map, D_frontier, stack_level+1) == SUCCESS )
        return SUCCESS;

    imply(net, val, backtrace_pair.net, X, net_map, gate_map, value_map, in_vec, out_vec, D_frontier);

    return FAIL;
}


void printTestSequence(map<int, int> &value_map, vector<int> &input)
{
    if (DEBUG) {
        cout << "=======================================" << endl;
        cout << "Printing Test Sequence..." << endl;
    }
    int v;
    for (auto &in : input)
    {
        v = value_map[in];
        if (v == 0)
            cout << "0";
        else if (v == 1)
            cout << "1";
        else if (v == D)
            cout << "1";
        else if (v == DBAR)
            cout << "0";
        else if (v == X)
            cout << "X";
    }
    cout << endl;
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
    //cout << faulty_net << " FAULTY NET: " << endl;
    //const char *faulty_val = argv[3];

    // variable init
    map<int, vector<int>> net_map;
    map<int, Gate*> gate_map;
    vector<int> in_vec;
    vector<int> out_vec;
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
    
    if (DEBUG) {
        cout << "NET MAP" << endl;
        printNetMap(net_map);
        cout << "VALUE MAP" << endl;
        printNetVals(value_map);
    }

    // Run PODEM
    int ret_code = podem(faulty_net, faulty_val, net_map, gate_map, in_vec, out_vec, net_driver, value_map, D_frontier, 0);
   
    if (DEBUG) {
        cout << "PODEM RETURNS: " << ret_code << endl;
        cout << "FINAL VALUE MAP: " << endl;
        printNetVals(value_map);
    }

    // determine the test sequence
    if (ret_code == SUCCESS)
        printTestSequence(value_map, in_vec);
    else
        cout << "Undetectable" << endl;

    return 0;
}
