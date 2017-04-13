#include "instruction.hpp"

namespace arbiter
{

//public
Instruction::Instruction(const Instruction &other): _operand_A(other._operand_A), _operand_B(other._operand_B), _op_code(other._op_code)
{}

Instruction::Instruction(const Opcode op_code, const Operand &operand_A, const Operand &operand_B): _operand_A(operand_A), _operand_B(operand_B), _op_code(op_code)
{}

Instruction& Instruction::operator =(const Instruction& other)
{
    if(this==&other)
        return *this;
    _operand_A = other._operand_A;
    _operand_B = other._operand_B;
    _op_code = other._op_code;
    return *this;
}

Operand Instruction::operandA()
{
    return _operand_A;
}
Operand Instruction::operandB()
{
    return _operand_B;
}
void Instruction::setOperandA(const Operand &operand)
{
    _operand_A = operand;
}
void Instruction::setOperandB(const Operand &operand)
{
    _operand_B = operand;
}


Opcode Instruction::instructionType()
{
    return _op_code;
}
void Instruction::setInstructionType(const Opcode op_code)
{
    _op_code = op_code;
}

//private
Instruction::Instruction(): _operand_A(), _operand_B(), _op_code()
{}

}
