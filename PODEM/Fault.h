#ifndef FAULT_H
#define FAULT_H

#include <iostream>
#include <vector>
#include <map>

#define DEBUG 0

struct fault {
    int net;
    int sa;
    
    bool operator < (const fault& f) const
    {
        return (net < f.net);
    }

    bool operator == (const fault& f) const
    {
        return (net == f.net && sa == f.sa);
    }
};

bool compareFaults(fault f1, fault f2);
void printFaults(std::map<int, std::vector<fault>> &m);
void printFaultVec(std::vector<fault> &v);
void updateFaultMap(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &fault_vec, int net, int sa_val);
void unionFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2);
void subtractFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2);
void intersectFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2);
void evenFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2);
#endif
