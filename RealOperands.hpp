#ifndef REALOPERANDS_HPP
#define REALOPERANDS_HPP

#include "Operand.hpp"


namespace arbiter
{

    class ImmidiateOperand: public Operand
    {
    public:
        ImmidiateOperand(const ImmidiateOperand& other);
        explicit ImmidiateOperand(const IntegerRegister &value);
        ImmidiateOperand(const ImmidiateOperand &&other);


        virtual Operand::OperandPtr clone()const;
        virtual IntegerRegister countArgument(CorePtr core);
    };

    class DirectOperand: public Operand
    {
    public:
        OperandPtr clone();
        IntegerRegister countArgument(CorePtr core);
    };

    class IndirectOperand: public Operand
    {
    public:
        OperandPtr clone();
        IntegerRegister countArgument(CorePtr core);
    };

    class IndirectDecrementOperand: public Operand
    {
    public:
        OperandPtr clone();
        IntegerRegister countArgument(CorePtr core);
    };

    class IndirectIncrementOperand: public Operand
    {
    public:
        OperandPtr clone();
        IntegerRegister countArgument(CorePtr core);
    };

}

#endif // REALOPERANDS_HPP

