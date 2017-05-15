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

    Instruction::Instruction( Instruction &&other): operand_A_(other.operand_A_.release() ), operand_B_( other.operand_B_.release() )
    {
      //  other.operand_A_ = nullptr;
       // other.operand_B_ = nullptr;
    }

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


    Instruction& Instruction::operator=(const Instruction& other)
    {
        if(this == &other)
            return *this;

        operand_A_.reset();//kasujemy to co dotychczas trzymalismy
        operand_B_.reset();

        operand_A_ = other.operand_A_->clone();//przejmujemy nowe operandy
        operand_B_ = other.operand_B_->clone();
        return *this;
    }

    Instruction& Instruction::operator=(Instruction &&other)
    {
        if(this == &other)
            return *this;

        operand_A_.reset();//kasujemy to co dotychczas trzymalismy
        operand_B_.reset();

        operand_A_ = OperandPtr(other.operand_A_.release() );
        operand_B_ = OperandPtr(other.operand_B_.release() );
        return *this;
    }

/*
    std::vector<std::unique_ptr<Instruction> >&& copyInstructionVector(const std::vector<std::unique_ptr<Instruction> > copied_vect)
    {
        std::vector<std::unique_ptr<Instruction> > returned(copied_vect.size());
        for(auto iter = copied_vect.begin(); iter != copied_vect.end(); ++iter)
        {
            returned.push_back( (*iter)->clone() );
        }
        return std::move(returned);

    }
*/

}
