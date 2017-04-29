#ifndef REALOPERANDS_HPP
#define REALOPERANDS_HPP

#include "Operand.hpp"


namespace arbiter
{

    class ImmidiateOperand: public Operand
    {

        OperandPtr clone();
        IntegerRegister countArgument();
    };

    class DirectOperand: public Operand
    {
        OperandPtr clone();
        IntegerRegister countArgument();
    };

    class IndirectOperand: public Operand
    {
        OperandPtr clone();
        IntegerRegister countArgument();
    };

    class IndirectDecrementOperand: public Operand
    {
        OperandPtr clone();
        IntegerRegister countArgument();
    };

    class IndirectIncrementOperand: public Operand
    {
        OperandPtr clone();
        IntegerRegister countArgument();
    };

}

#endif // REALOPERANDS_HPP

