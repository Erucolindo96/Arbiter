#include "Instruction.hpp"

namespace arbiter
{
    typedef std::shared_ptr<Core> CorePtr;
    typedef std::unique_ptr<Operand> OperandPtr;


//public


    Instruction::Instruction():operand_A_(), operand_B_()
    {}

    Instruction::Instruction(const Instruction &other): operand_A_(other.operand_A_->clone()), operand_B_(other.operand_B_->clone())
    {}

   // Instruction::Instruction(const Instruction &&other): operand_A_(std::move(other.operand_A_)), operand_B_(std::move(other.operand_B_))
   // {}

    OperandPtr Instruction::operandA() const
    {
        return operand_A_->clone();
    }
    OperandPtr Instruction::operandB() const
    {
        return operand_B_->clone();
    }

    void Instruction::setOperandA(const OperandPtr& operand)
    {
        operand_A_ = operand->clone();
    }

    void Instruction::setOperandB(const OperandPtr& operand)
    {
        operand_B_ = operand->clone();
    }




    /*
//public

Instruction::Instruction(): operand_A_(), operand_B_(), core_(nullptr)
{}

Instruction::Instruction(const Instruction &other): operand_A_(other.operand_A_), operand_B_(other.operand_B_), core_(other.core_)
{}

Instruction::Instruction(const Operand &operand_A, const Operand &operand_B, const CorePtr &core_ptr): operand_A_(operand_A), operand_B_(operand_B), core_(core_ptr)
{
    if(operand_A.core_ != core_ptr_ || operand_B.core_ != core_ptr)
        throw std::invalid_argument("Instruction: invalid arguments in constructor(Operand, Operand, Shared_ptr<Core>) - another core_ptr\n");

}


Instruction& Instruction::operator=(const Instruction& other)//zakładam, że instrukcja other ma poprawne operandy
{
    if(this==&other)
        return *this;
    operand_A_ = other.operand_A_;
    operand_B_ = other.operand_B_;
    core_ = other.core_;
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

}
void Instruction::setOperandB(const Operand &operand)
{
    operand_B_ = operand;
}




*/


}
