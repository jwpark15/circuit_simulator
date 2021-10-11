#include <iostream>
#include <vector>

#include "Gate.h"

Gate::Gate()
{
    out = -1;
    in1 = -1;
    in2 = -1;
}

void Gate::setInput(int x)
{
    if (in1 == -1) {
        in1 = x;
    } else {
        in2 = x;
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
        
