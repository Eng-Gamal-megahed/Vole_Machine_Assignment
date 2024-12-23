#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "Vole_Machine.h"

using namespace std;

//========================================================Walid Adel ===========================================================================

// Load (1) to store the content of some cell in memory in the registre
void CPU::load(int cell_of_reg, int cell_of_memo, Register &reg, Memory &memo)
{
    reg.set_cell(cell_of_reg, memo.get_cell(cell_of_memo));
}

// Load (2) to store the input direct in register (done)
void CPU::load(int index_of_reg, int val, Register &reg)
{
    reg.set_cell(index_of_reg, dec_to_hexa(val));
}

void CPU::store(int cell_in_reg, int cell_in_memo, Register &reg, Memory &memo)
{
    memo.set_cell(cell_in_memo, reg.get_cell(cell_in_reg));
}

void CPU::move(int cell1, int cell2, Register &reg)
{
    // Move the content of cell1 to cell2 in register.
    reg.set_cell(cell2, reg.get_cell(cell1));
}

void CPU::jumpB(int cell_reg, int cell_mem, Register &reg)
{
    // if (reg.get_cell(0) == reg.get_cell(cell_reg))
    // {
    //     PC = cell_mem;
    // }
}

void CPU::jumpD(int cellR, int cellXY, Register &reg)
{
    if (get_twos_comp(reg.get_cell(cellR)) > get_twos_comp(reg.get_cell(0)))
    {
        PC = cellXY;
    }
}

#include <string>
#include <cctype>

string lower(string str)
{
    for (char &ch : str)
    {
        ch = tolower(ch);
    }
    return str;
}

bool is_valid(string stru)
{
    stru = lower(stru);

    for (size_t i = 0; i < stru.size() - 1; i++)
    { 
        if (stru[i] == '0' && stru[i + 1] == 'x')
        {
            stru.erase(i, 2);
            i--;
        }
    }

    if (stru.size() == 4)
    {
        for (short i = 0; i < 4; i++)
        {
            if (!((stru[i] >= '0' && stru[i] <= '9') || (stru[i] >= 'a' && stru[i] <= 'f')))
                return false;
        }
        return true;
    }
    return false;
}

// ==================================================== Gamal =================================================


bool CPU::runNextStep()
{
    fetch();
    execute(decode());
    return true;
}


void CPU::Rotate(int cell , int moves , Register &reg)
{
    int val = stoi(reg.get_cell(cell) , nullptr , 16);
    val = (val >> moves) | (val << (8 - moves));
    reg.set_cell(cell , dec_to_hexa(val));
}

void CPU::add5(int cellR, int cellS, int cellT, Register &reg)
{
    int vals = get_twos_comp(stoi(reg.get_cell(cellS), nullptr, 16));
    int valt = get_twos_comp(stoi(reg.get_cell(cellT), nullptr, 16));
    int result = vals + valt;
    reg.set_cell(cellR, dec_to_hexa(result));
}

void CPU::add6(int cellR, int cellS, int cellT, Register &reg)
{
    float vals = get_float(stoi(reg.get_cell(cellS), nullptr, 16));
    float valt = get_float(stoi(reg.get_cell(cellT), nullptr, 16));
    float result = vals + valt;
    int dec = convert_from_float(get_binary(result));
    reg.set_cell(cellR, dec_to_hexa(dec));
}

string Memory::get_cell(int idx)
{
    return memory[idx];
}

void Memory::set_cell(int idx, string code)
{

    memory[idx] = code;
}

string Register::get_cell(int idx)
{
    return memory[idx];
}

void Register::set_cell(int index, string val)
{
    memory[index] = val;
}

string CPU::dec_to_hexa(int val)
{
    stringstream stream;
    stream << hex << uppercase << (val & 0xFF);
    return stream.str();
}

int CPU::get_twos_comp(int val)
{
    if (val & 0x80)
    {
        return val - 256;
    }
    else
    {
        return val;
    }
}

float CPU::get_float(int val)
{
    float mantissa = val & ((1 << 4) - 1);
    val -= mantissa;
    mantissa *= pow(2, -4);
    int exponent = (val & ((1 << 7) - 1)) * pow(2, -4);
    float result = mantissa * pow(2, exponent - 4);
    if (val & (1 << 7))
        result *= -1;
    return result;
}

string CPU::get_binary(float value)
{
    string binary;
    if (value < 0)
    {
        binary += '-';
        value = -value;
    }
    int intPart = value;
    float fracPart = value - intPart;
    string intBinary;
    while (intPart > 0)
    {
        intBinary = to_string(intPart % 2) + intBinary;
        intPart /= 2;
    }
    if (intBinary.empty())
    {
        intBinary = "0";
    }
    string fracBinary;
    while (fracPart > 0)
    {
        fracPart *= 2;
        int bit = fracPart;
        fracBinary += to_string(bit);
        fracPart -= bit;
    }
    return binary + intBinary + (fracBinary.empty() ? "" : "." + fracBinary);
}

int CPU::convert_from_float(string float_bin)
{
    string result = "0";
    int dot_idx = float_bin.find('.');
    int frst_one_idx = float_bin.find('1');
    if (float_bin[0] == '-')
        dot_idx--, frst_one_idx--, result[0] = '1';
    string mantissa;
    for (int i = 0; i < float_bin.size(); ++i)
    {
        if (isdigit(float_bin[i]))
        {
            mantissa += float_bin[i];
        }
    }
    result += get_binary(dot_idx - frst_one_idx + 4) + mantissa;
    return stoi(result, nullptr, 2);
}

// ====================================== Mustafa =======================================================

void CPU::fetch()
{
    IR = ptr->get_cell(PC);
    PC++; // Increment the Program Counter to the next instruction
    IR += ptr->get_cell(PC);
    PC++;
}

vector<int> CPU::decode()
{

    vector<int> operation(3);
    operation[0] = stoi(string(1, IR[0]), nullptr, 16);
    operation[1] = stoi(string(1, IR[1]), nullptr, 16);
    operation[2] = stoi(IR.substr(2, 2), nullptr, 16);

    return operation;
}

<<<<<<< HEAD
bool CPU::execute(vector<int>vec){
=======
void CPU::execute(Register &, Memory *, vector<int> vec)
{
>>>>>>> 6639ad5b129633573cc7ffabd57b9854f4b2e065

    string reg_address = dec_to_hexa(vec[2]);

    if (vec[0] == 1)
    {
        load(vec[1], vec[2], reg, *ptr); // the value is converted into decimal and stored ******* not hex
    }

    else if (vec[0] == 2)
    {
        load(vec[1], vec[2], reg);
    }

    else if (vec[0] == 3)
    {

        if (vec[2] == 0)
        {
            screen += reg.get_cell(vec[1]);
        }

        store(vec[1], vec[2], reg, *ptr);
    }

    else if (vec[0] == 4)
    {
        move(stoi(string(1, reg_address[0]), nullptr, 16), stoi(string(1, reg_address[1]), nullptr, 16), reg);
    }

    else if (vec[0] == 5)
    {
        add5(vec[1], stoi(string(1, reg_address[0]), nullptr, 16), stoi(string(1, reg_address[1]), nullptr, 16), reg);
    }

    else if (vec[0] == 6)
    {
        add6(vec[1], stoi(string(1, reg_address[0]), nullptr, 16), stoi(string(1, reg_address[1]), nullptr, 16), reg);
    }

    else if (vec[0] == 7)
    {
        OR(vec[1], stoi(string(1, reg_address[0]), nullptr, 16), stoi(string(1, reg_address[1]), nullptr, 16), reg);
    }

    else if (vec[0] == 8)
    {
        AND(vec[1], stoi(string(1, reg_address[0]), nullptr, 16), stoi(string(1, reg_address[1]), nullptr, 16), reg);
    }

    else if (vec[0] == 9)
    {
        XOR(vec[1], stoi(string(1, reg_address[0]), nullptr, 16), stoi(string(1, reg_address[1]), nullptr, 16), reg);
    }

    else if (vec[0] == 10)
    {
        Rotate(vec[1], vec[2], reg);
    }

    else if (vec[0] == 11)
    {
        jumpB(vec[1], vec[2], reg);
    }

    else if (vec[0] == 12 && vec[1] == 0 && vec[2] == 0)
    {
        return false;
    }

    else if (vec[0] == 13)
    {
        jumpD(vec[1], vec[2], reg);
    }
<<<<<<< HEAD
    return true;
=======
>>>>>>> 6639ad5b129633573cc7ffabd57b9854f4b2e065
}

void CPU::OR(int result_reg, int reg1, int reg2, Register &reg)
{
<<<<<<< HEAD
    reg.set_cell( result_reg , dec_to_hexa( stoi( reg.get_cell(reg1)  , nullptr, 16) | stoi( reg.get_cell(reg2)  , nullptr, 16) ) );
=======
    reg.set_cell(result_reg, dec_to_hexa(reg1 | reg2));
>>>>>>> 6639ad5b129633573cc7ffabd57b9854f4b2e065
}

void CPU::AND(int result_reg, int reg1, int reg2, Register &reg)
{
<<<<<<< HEAD
    reg.set_cell( result_reg , dec_to_hexa( stoi( reg.get_cell(reg1)  , nullptr, 16) & stoi( reg.get_cell(reg2)  , nullptr, 16) ) );
=======
    reg.set_cell(result_reg, dec_to_hexa(reg1 & reg2));
>>>>>>> 6639ad5b129633573cc7ffabd57b9854f4b2e065
}

void CPU::XOR(int result_reg, int reg1, int reg2, Register &reg)
{
<<<<<<< HEAD
    reg.set_cell( result_reg , dec_to_hexa(  stoi( reg.get_cell(reg1)  , nullptr, 16) ^  stoi( reg.get_cell(reg2)  , nullptr,16)));
}
=======
    reg.set_cell(result_reg, dec_to_hexa(reg1 ^ reg2));
}
>>>>>>> 6639ad5b129633573cc7ffabd57b9854f4b2e065
