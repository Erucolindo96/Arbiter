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

    Instruction::Instruction(const OperandPtr &operand_A, const OperandPtr &operand_B): operand_A_(operand_A->clone()), operand_B_(operand_B->clone())
    {}

    //Instruction::Instruction(const Instruction &&other): operand_A_(other.operand_A_.release()), operand_B_(other.operand_B_.release())
    //{
       // other.operand_A_ = nullptr;
       // other.operand_B_ = nullptr;
    //}

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

    Instruction::~Instruction()
    {}

//protected
    Instruction& Instruction::operator=(const Instruction& other)
    {
        if(this == &other)
            return *this;
        operand_A_ = other.operand_A_->clone();
        operand_B_ = other.operand_B_->clone();
        return *this;
    }


}
