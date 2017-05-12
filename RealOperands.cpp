#include"RealOperands.hpp"

namespace arbiter
{

    ImmidiateOperand::ImmidiateOperand(const ImmidiateOperand& other): Operand(other)
    {}

    ImmidiateOperand::ImmidiateOperand(const IntegerRegister &value): Operand(value)
    {}

    ImmidiateOperand::ImmidiateOperand(const ImmidiateOperand &&other): Operand(other)
    {}


    Operand::OperandPtr ImmidiateOperand::clone()const
    {
        return Operand::OperandPtr(new ImmidiateOperand(*this) );
    }

    IntegerRegister ImmidiateOperand::countArgument(CorePtr core)
    {
        return value_;//bo jest natychmiastowy
    }

}


