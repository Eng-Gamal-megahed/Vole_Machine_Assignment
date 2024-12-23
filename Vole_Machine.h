
/*
                                 *****  Operations Set  *******


    1 RXY LOAD the register R with the bit pattern found in the memory cell whose address is XY.
    Example: 14A3 would cause the contents of the memory cell located at address A3 to be placed in register 4.

    2 RXY LOAD the register R with the bit pattern XY.
    Example: 20A3 would cause the value A3 to be placed in register 0.

    3 RXY STORE the bit pattern found in register R in the memory cell whose address is XY.
    Example: 35B1 would cause the contents of register 5 to be placed in the memory cell whose address is B1.

    3 R00 STORE to location 00, which is a memory mapping for the screen. Writing to 00 is writing to screen.

    4 0RS MOVE the bit pattern found in register R to register S.
    Example: 40A4 would cause the contents of register A to be copied into register 4.

    5 RST ADD the bit patterns in registers S and T as though they were two’s complement representations and leave the result in register R.
    Example: 5726 would cause the binary values in registers 2 and 6 to be added and the sum placed in register 7.

    6 RST ADD the bit patterns in registers S and T as though they represented values in floating-point notation and leave the floating-point result in register R.
    Example: 634E would cause the values in registers 4 and E to be added as floating-point values and the result to be placed in register 3.

    7 RST Bitwise OR (V) the content of register S and T, and put the result in register R.

    8 RST Bitwise AND (A) the content of register S and T, and put the result in register R.

    9 RST Bitwise XOR (+) the content of register S and T, and put the result in register R.

    A RxX Rotate the content of register R cyclically right X steps.

    B RXY JUMP to the instruction located in the memory cell at address XY if the bit pattern in register R
            is equal to the bit pattern in register number 0. Otherwise, continue with the normal sequence of
            execution. (The jump is implemented by copying XY into the program counter during the execute phase.)
    Example: B43C would first compare the contents of register 4 with the contents of register 0. If
            the two were equal, the pattern 3C would be placed in the program counter so that the next
            instruction executed would be the one located at that memory address. Otherwise, nothing would be done and program execution would continue in its normal sequence.

    C 000 HALT execution.
    Example: C000 would cause program execution to stop.

    D RXY Jump to instructor RAM cell XY if the content of register R is greater than (>) the integers in two's-complement notation.
*/

#include <iostream>
#include <vector>
#include <string>
#include <QMessageBox>

using namespace std;

class CPU;
class Register;
class Memory;


bool is_valid(string);

class Register
{
private:
    string memory[16];
    int size = 16;

public:
    string get_cell(int);
    void set_cell(int, string);
};

class Memory
{
private:
    string memory[256];
    int size = 256;

public:
    string get_cell(int);
    void set_cell(int, string);
};

class CPU
{
private:
    Memory *ptr;
    int PC;
    string IR;
    Register reg;
    string screen;
public:
    CPU(Memory *memory) : ptr(memory), PC(0), IR("") {}
    string get_screen()
    {
        return screen;
    }
    Register get_reg()
    {
        return reg;
    }
    string dec_to_hexa(int);
    int get_twos_comp(int);
    float get_float(int);
    int convert_from_float(string);
    string get_binary(float);
    void add5(int, int, int, Register &);
    void add6(int, int, int, Register &);
    void load(int, int , Register &, Memory &);
    void load(int, int, Register &);
    void store(int,int, Register &, Memory &);
    void move(int, int, Register &);
    void jumpB(int, int, Register &);
    void halt();
    bool runNextStep();
    void fetch();
    vector<int> decode();
    bool execute(vector<int>);
    //
    void OR(int, int, int, Register &);
    void AND(int, int, int, Register &);
    void XOR(int, int, int, Register &);
    void jumpD(int, int, Register &);
    void Rotate(int , int , Register &);
    //
};


