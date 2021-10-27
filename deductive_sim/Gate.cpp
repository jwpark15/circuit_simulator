#include "Gate.h"

Gate::Gate(int i1, int i2, int io)
    : out(-1), 
      in1(-1), 
      in2(-1),
      net1(i1), 
      net2(i2), 
      netout(io)
{}

void Gate::setInput(int x, int net)
{
    if (net1 == net) {
        in1 = x;
    } else if (net2 == net) {
        in2 = x;
    } else {
        std::cout << "=== NO MATCHING NET ===" << std::endl;
    }
}


bool Gate::areInputsSet()
{
    if (in1 != -1 && in2 != -1) {
        return true;
    } else {
        return false;
    }
}


void INVGate::setInput(int x, int net)
{
    if (net1 == net) {
        in1 = x;
        in2 = x;
    } else {
        std::cout << "=== NO MATCHING NET ===" << std::endl;
    }
}

void BUFGate::setInput(int x, int net)
{
    if (net1 == net) {
        in1 = x;
        in2 = x;
    } else {
        std::cout << "=== NO MATCHING NET ===" << std::endl;
    }
}

int INVGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 ? 0 : 1);
        return 1;
    } else {
        return 0;
    }
}

void INVGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    auto itr = fault_map.find(net1);
    if (itr != fault_map.end()) 
    {
        //add fault vec of net 1 to netout
        std::vector<fault> temp_vec = fault_map[net1];
        fault_map.insert(std::make_pair(netout, temp_vec));
    }
    updateFaultMap(fault_map, potential_faults, netout, in1);
}
        
int BUFGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = in1;
        return 1;
    } else {
        return 0;
    }
}
        
void BUFGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    auto itr = fault_map.find(net1);
    if (itr != fault_map.end()) 
    {
        // add fault vec of net 1 to netout
        std::vector<fault> temp_vec = fault_map[net1];
        fault_map.insert(std::make_pair(netout, temp_vec));
    }
    // since gate is BUF, add s-a val opposite of in1 val
    int temp = (in1) ? 0 : 1;
    updateFaultMap(fault_map, potential_faults, netout, temp);
}

int ANDGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 && in2);
        return 1;
    } else {
        return 0;
    }
}
        
void ANDGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    if (in1 && in2) 
    {
        // both non controlling
        unionFaults(fault_map, netout, net1, net2);
    } else if (in1 && !in2) {
        // in2 is controlling
        subtractFaults(fault_map, netout, net2, net1);
    } else if (!in1 && in2) {
        // in1 is controlling
        subtractFaults(fault_map, netout, net1, net2);
    } else if (!in1 && !in2) {
        // both controlling
        intersectFaults(fault_map, netout, net1, net2); 
    }
    int temp = (out) ? 0 : 1;
    updateFaultMap(fault_map, potential_faults, netout, temp);
}

int NANDGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = ((in1 && in2) ? 0 : 1);
        return 1;
    } else {
        return 0;
    }
}
        
void NANDGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    if (in1 && in2) 
    {
        // both non controlling
        unionFaults(fault_map, netout, net1, net2);
    } else if (in1 && !in2) {
        // in2 is controlling
        subtractFaults(fault_map, netout, net2, net1);
    } else if (!in1 && in2) {
        // in1 is controlling
        subtractFaults(fault_map, netout, net1, net2);
    } else if (!in1 && !in2) {
        // both controlling
        intersectFaults(fault_map, netout, net1, net2); 
    }
    int temp = (out) ? 0 : 1;
    updateFaultMap(fault_map, potential_faults, netout, temp);

}

int ORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 || in2);
        return 1;
    } else {
        return 0;
    }
}
        
void ORGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    if (!in1 && !in2) 
    {
        // both non controlling
        unionFaults(fault_map, netout, net1, net2);
    } else if (!in1 && in2) {
        // in2 is controlling
        subtractFaults(fault_map, netout, net2, net1);
    } else if (in1 && !in2) {
        // in1 is controlling
        subtractFaults(fault_map, netout, net1, net2);
    } else if (in1 && in2) {
        // both controlling
        intersectFaults(fault_map, netout, net1, net2); 
    }
    int temp = (out) ? 0 : 1;
    updateFaultMap(fault_map, potential_faults, netout, temp);
}

int NORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = ((in1 || in2) ? 0 : 1);
        return 1;
    } else {
        return 0;
    }
}
        
void NORGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    if (!in1 && !in2) 
    {
        // both non controlling
        unionFaults(fault_map, netout, net1, net2);
    } else if (!in1 && in2) {
        // in2 is controlling
        subtractFaults(fault_map, netout, net2, net1);
    } else if (in1 && !in2) {
        // in1 is controlling
        subtractFaults(fault_map, netout, net1, net2);
    } else if (in1 && in2) {
        // both controlling
        intersectFaults(fault_map, netout, net1, net2); 
    }
    int temp = (out) ? 0 : 1;
    updateFaultMap(fault_map, potential_faults, netout, temp);
}

int XORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 ^ in2);
        return 1;
    } else {
        return 0;
    }
}
        
void XORGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    int temp = (out) ? 0 : 1;
    updateFaultMap(fault_map, potential_faults, netout, temp);
    std::cout << " THIS IS XOR " << std::endl;
}

int XNORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = ((in1 ^ in2) ? 0 : 1);
        return 1;
    } else {
        return 0;
    }
}
        
void XNORGate::updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
{
    int temp = (out) ? 0 : 1;
    updateFaultMap(fault_map, potential_faults, netout, temp);
    std::cout << " THIS IS XNOR " << std::endl;
}

