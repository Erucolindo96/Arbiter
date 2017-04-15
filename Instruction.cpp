#include "Instruction.hpp"

namespace arbiter
{

//public

Instruction::Instruction(): operand_A_(NULL, 0), operand_B_(NULL, 0)
{}

Instruction::Instruction(const Instruction &other): operand_A_(other.operand_A_), operand_B_(other.operand_B_)
{}

Instruction::Instruction(const Operand &operand_A, const Operand &operand_B): operand_A_(operand_A), operand_B_(operand_B)
{}


Instruction& Instruction::operator=(const Instruction& other)//zakładam, że instrukcja other ma poprawne operandy
{
    if(this==&other)
        return *this;
    operand_A_ = other.operand_A_;
    operand_B_ = other.operand_B_;
    return *this;
}

Operand Instruction::operandA() const
{
    return operand_A_;
}
Operand Instruction::operandB() const
{
    return operand_B_;
}

void Instruction::setOperandA(const Operand &operand)
{
    operand_A_ = operand;
    checkAddressingType(operand);

}
void Instruction::setOperandB(const Operand &operand)
{
    operand_B_ = operand;
    checkAddressingType(operand);
}






}
