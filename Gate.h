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
    public:
        Gate();
        int getout() {return out;}
        int get1() {return in1;}
        int get2() {return in2;}
        virtual void setInput(int x);
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
        INVGate() {std::cout << "Creating INV" << std::endl;}
        int evaluate();
};

class BUFGate : public Gate 
{
    public:
        BUFGate() {std::cout << "Creating BUF" << std::endl;}
        int evaluate();

};

class ANDGate : public Gate 
{
    public:
        ANDGate() {std::cout << "Creating AND" << std::endl;}
        int evaluate();

};

class NANDGate : public Gate 
{
    public:
        NANDGate() {std::cout << "Creating NAND" << std::endl;}
        int evaluate();

};

class ORGate : public Gate 
{
    public:
        ORGate() {std::cout << "Creating OR" << std::endl;}
        int evaluate();

};

class NORGate : public Gate 
{
    public:
        NORGate() {std::cout << "Creating NOR" << std::endl;}
        int evaluate();

};

class XORGate : public Gate 
{
    public:
        XORGate() {std::cout << "Creating XOR" << std::endl;}
        int evaluate();

};

class XNORGate : public Gate 
{
    public:
        XNORGate() {std::cout << "Creating XNOR" << std::endl;}
        int evaluate();

};

#endif
