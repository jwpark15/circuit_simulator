#ifndef GATE_H
#define GATE_H

#include <vector>
#include <iostream>

class Gate 
{
    protected:
        int out;
        int in1;
        int in2;
        int net1;
        int net2;
        int netout;
    public:
        Gate() {}
        Gate(int i1, int i2, int io);
        int getOut() {return out;}
        int get1() {return in1;}
        int get2() {return in2;}
        int getNet1() {return net1;}
        int getNet2() {return net2;}
        int getNetout() {return netout;}
        virtual void setInput(int x, int net);
        bool areInputsSet();
        virtual int evaluate() 
        {
            std::cout << "Evaluating gate..." << std::endl;
            return 0;
        }
};

class INVGate: public Gate
{
    public:
        INVGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        void setInput(int x, int net);
        int evaluate();
};

class BUFGate : public Gate 
{
    public:
        BUFGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        void setInput(int x, int net);
        int evaluate();

};

class ANDGate : public Gate 
{
    public:
        ANDGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        int evaluate();

};

class NANDGate : public Gate 
{
    public:
        NANDGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        int evaluate();

};

class ORGate : public Gate 
{
    public:
        ORGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        int evaluate();
};

class NORGate : public Gate 
{
    public:
        NORGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        int evaluate();
};

class XORGate : public Gate 
{
    public:
        XORGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        int evaluate();

};

class XNORGate : public Gate 
{
    public:
        XNORGate(int i1, int i2, int io) : Gate(i1, i2, io) {}
        int evaluate();

};

#endif
