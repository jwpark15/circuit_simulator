#ifndef GATE_H
#define GATE_H

#include <vector>
#include <iostream>
#include <map>

#include "Fault.h"

#define D 2
#define DBAR 3
#define X 4

class Gate 
{
    protected:
        int out;
        int in1;
        int in2;
        int net1;
        int net2;
        int netout;
        int i_parity;
        int control_val;
    public:
        Gate() {}
        Gate(int i1, int i2, int io);
        int getOut() {return out;}
        int get1() {return in1;}
        int get2() {return in2;}
        int getNet1() {return net1;}
        int getNet2() {return net2;}
        int getNetout() {return netout;}
        int getParity() {return i_parity;}
        int getControlling() {return control_val;}
        virtual void setInput(int x, int net);
        bool areInputsSet();
        virtual int evaluate() 
        {
            std::cout << "Evaluating gate..." << std::endl;
            return 0;
        }
        virtual void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults)
        {
            std::cout << "updating fault list..." << std::endl;
        }
};

class INVGate: public Gate
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5] = {1, 0, DBAR, D, X};
    public:
        INVGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 1;
            control_val = -1;
        }
        void setInput(int x, int net);
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

class BUFGate : public Gate 
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5] = {0, 1, D, DBAR, X};
    public:
        BUFGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 0;
            control_val = -1;
        }
        void setInput(int x, int net);
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

class ANDGate : public Gate 
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5][5] = {
            {0, 0, 0, 0, 0},
            {0, 1, D, DBAR, X},
            {0, D, D, 0, X},
            {0, DBAR, 0, DBAR, X},
            {0, X, X, X, X}
        };
    public:
        ANDGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 0;
            control_val = 0;
        }
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

class NANDGate : public Gate 
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5][5] = {
            {1, 1, 1, 1, 1},
            {1, 0, DBAR, D, X},
            {1, DBAR, DBAR, 1, X},
            {1, D, 1, D, X},
            {1, X, X, X, X}
        };
    public:
        NANDGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 1;
            control_val = 0;
        }
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

class ORGate : public Gate 
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5][5] = {
            {0, 1, D, DBAR, X},
            {1, 1, 1, 1, 1},
            {D, 1, D, 1, X},
            {DBAR, 1, 1, DBAR, X},
            {X, 1, X, X, X}
        };
    public:
        ORGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 0;
            control_val = 1;
        }
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

class NORGate : public Gate 
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5][5] = {
            {1, 0, DBAR, D, X},
            {0, 0, 0, 0, 0},
            {DBAR, 0, DBAR, 0, X},
            {D, 0, 0, D, X},
            {X, 0, X, X, X}
        };
    public:
        NORGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 1;
            control_val = 1;
        }
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

class XORGate : public Gate 
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5][5] = {
            {0, 1, D, DBAR, X},
            {1, 0, DBAR, D, X},
            {D, DBAR, 0, 1, X},
            {DBAR, D, 1, 0, X},
            {X, X, X, X, X}
        };
    public:
        XORGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 0;
            control_val = -1;
        }
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

class XNORGate : public Gate 
{
    protected: 
        // 0 1 D DBAR X
        int D_calc[5][5] = {
            {1, 0, DBAR, D, X},
            {0, 1, D, DBAR, X},
            {DBAR, D, 1, 0, X},
            {D, DBAR, 0, 1, X},
            {X, X, X, X, X}
        };
    public:
        XNORGate(int i1, int i2, int io) : Gate(i1, i2, io) {
            i_parity = 1;
            control_val = -1;
        }
        int evaluate();
        void updateFaultList(std::map<int, std::vector<fault>> &fault_map, std::vector<fault> &potential_faults);
};

#endif
