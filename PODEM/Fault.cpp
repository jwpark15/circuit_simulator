#include "Fault.h"

bool compareFaults(fault f1, fault f2) 
{
    bool out;
    if ((f1.net == f2.net) && (f1.sa == f2.sa)) 
        out = true;
    else    
        out = false;
    return out;
}

void printFaults(std::map<int, std::vector<fault>> &m) 
{
    if(DEBUG)
    {
        std::cout << "=== FAULTS ===" << std::endl;
        for (auto itr = m.begin(); itr != m.end(); ++itr)
        {   
            std::cout << "NET: " << itr->first << "\tFAULTS: ";
            for (auto &v : itr->second)
                std::cout << "(" << v.net << " " << v.sa << ")  ";
            std::cout << std::endl;
        }   
        std::cout << "=== END FAULTS ===" << std::endl;
    }
}

void printFaultVec(std::vector<fault> &v)
{
    if(DEBUG)
    {
        std::cout << "=== FAULT VEC ===" << std::endl;
        for (auto &vf: v)
            std::cout << "(" << vf.net << " " << vf.sa << ")" << std::endl;
        std::cout << "=== END FAULT VEC ===" << std::endl;
    }
}

void updateFaultMap(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &fault_vec, int net, int sa_val)
{
    fault temp;
    temp.sa = sa_val;
    temp.net = net;
    // make sure fault is in potential list before adding to map
    bool potential = false;
    for (auto &p : fault_vec)
    {
        if (compareFaults(temp, p)) {
            potential = true;
            break;
        }
    }

    if (!potential)
        return;

    auto itr = fault_map.find(net);
    if (itr != fault_map.end()) {
        // make sure fault is not already in list
        bool exists = false;
        for (auto &v : fault_map[net])
        {
            if (compareFaults(v, temp)) {
                exists = true;
                break;
            }
        }

        // if does not exist in list already, add it
        if (!exists)
            fault_map[net].push_back(temp);

    } else {
        fault_map.insert(std::make_pair(net, std::vector<fault> {temp}));
    }
}

void unionFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2)
{
    auto itr1 = fault_map.find(net1);
    auto itr2 = fault_map.find(net2);
    std::vector<fault> temp;
    bool i1 = false;

    // add all faults from first list
    if (itr1 != fault_map.end()) {
        i1 = true;
        for (auto &v1 : fault_map[net1]) {
            temp.push_back(v1);
        }
    }

    // add faults from 2nd list, but check for overlap
    if (itr2 != fault_map.end()) {
        for (auto &v2 : fault_map[net2]) {
            bool exists = false;
            if (i1) {
                for (auto &v : fault_map[net1]) {
                    if (compareFaults(v, v2)) {
                        exists = true;
                        break;
                    }
                }
                if (!exists)
                    temp.push_back(v2);
            } else {
                temp.push_back(v2);
            }
        }
    }

    // update fault map
    auto itr = fault_map.find(newkey);
    if (itr != fault_map.end())
        std::cout << "\n\n==== BAD ===== " << newkey << std::endl;
    else
        fault_map.insert(std::make_pair(newkey, temp));

    printFaults(fault_map);
}

void subtractFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2)
{    
    auto itr1 = fault_map.find(net1);
    auto itr2 = fault_map.find(net2);
    std::vector<fault> temp;
    if (itr1 != fault_map.end()) {
        for (auto &v1 : fault_map[net1]) {
            bool equal = false;
            if (itr2 != fault_map.end()) {
                for (auto &v2 : fault_map[net2]) {
                    if (compareFaults(v1, v2)) {
                        equal = true;
                        break;
                    }
                }
            }
            if (!equal)
                temp.push_back(v1);
        }
    }
    // update fault map
    auto itr = fault_map.find(newkey);
    if (itr != fault_map.end())
        std::cout << "\n\n==== BAD ===== " << newkey << std::endl;
    else
        fault_map.insert(std::make_pair(newkey, temp));

    printFaults(fault_map);
}


void intersectFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2)
{   
    auto itr1 = fault_map.find(net1);
    auto itr2 = fault_map.find(net2);
    std::vector<fault> temp;
    if (itr1 != fault_map.end()) {
        for (auto &v1 : fault_map[net1]) {
            if (itr2 != fault_map.end()) {
                for (auto &v2 : fault_map[net2]) {
                    if (compareFaults(v1, v2))
                        temp.push_back(v2);
                }
            }
        }
    }

    // update fault map
    auto itr = fault_map.find(newkey);
    if (itr != fault_map.end())
        std::cout << "\n\n==== BAD ===== " << newkey << std::endl;
    else
        fault_map.insert(std::make_pair(newkey, temp));

    printFaults(fault_map);
}


void evenFaults(std::map<int, std::vector<fault>> &fault_map, int newkey, int net1, int net2)
{
    auto itr1 = fault_map.find(net1);
    auto itr2 = fault_map.find(net2);
    std::vector<fault> temp;
    bool i1 = false;

    // add all faults from first list
    if (itr1 != fault_map.end()) {
        i1 = true;
        for (auto &v1 : fault_map[net1]) {
            temp.push_back(v1);
        }
    }

    // add faults from 2nd list, but check for overlap
    if (itr2 != fault_map.end()) {
        for (auto &v2 : fault_map[net2]) {
            bool exists = false;
            if (i1) {
                int count = 0;
                for (auto &v : temp) {
                    if (compareFaults(v, v2)) {
                        exists = true;
                        temp.erase(temp.begin() + count);
                        break;
                    }
                    ++count;
                }
                if (!exists)
                    temp.push_back(v2);
            } else {
                temp.push_back(v2);
            }
        }
    }

    // update fault map
    auto itr = fault_map.find(newkey);
    if (itr != fault_map.end())
        std::cout << "\n\n==== BAD ===== " << newkey << std::endl;
    else
        fault_map.insert(std::make_pair(newkey, temp));

    printFaults(fault_map);
}
