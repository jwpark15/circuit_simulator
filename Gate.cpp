#include <iostream>
#include <vector>

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



int INVGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 ? 0 : 1);
        return 0;
    } else {
        return -1;
    }
}
        
int BUFGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = in1;
        return 0;
    } else {
        return -1;
    }
}
        
int ANDGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 && in2);
        return 0;
    } else {
        return -1;
    }
}
        
int NANDGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = ((in1 && in2) ? 0 : 1);
        return 0;
    } else {
        return -1;
    }
}
        
int ORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 || in2);
        return 0;
    } else {
        return -1;
    }
}
        
int NORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = ((in1 || in2) ? 0 : 1);
        return 0;
    } else {
        return -1;
    }
}
        
int XORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = (in1 ^ in2);
        return 0;
    } else {
        return -1;
    }
}
        
int XNORGate::evaluate()
{
    if(areInputsSet()) 
    {
        out = ((in1 ^ in2) ? 0 : 1);
        return 0;
    } else {
        return -1;
    }
}
        
