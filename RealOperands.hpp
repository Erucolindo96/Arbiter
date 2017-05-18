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
        virtual IntegerRegister countArgument(CorePtr &core, const IntegerRegister &instruction_PC)const;
    };

    class DirectOperand: public Operand
    {
    public:
        DirectOperand(const DirectOperand &other);
        explicit DirectOperand(const IntegerRegister &value);
        DirectOperand(const DirectOperand &&other);

        OperandPtr clone()const;
        IntegerRegister countArgument(CorePtr &core, const IntegerRegister &instruction_PC)const;
    };

    class IndirectOperand: public Operand
    {
    public:
        IndirectOperand(const IndirectOperand &other);
        explicit IndirectOperand(const IntegerRegister &value);
        IndirectOperand(const IndirectOperand &&other);


        OperandPtr clone()const;
        IntegerRegister countArgument(CorePtr &core, const IntegerRegister &instruction_PC)const;
    };

    class IndirectDecrementOperand: public Operand
    {
    public:
        IndirectDecrementOperand(const IndirectDecrementOperand &other);
        explicit IndirectDecrementOperand(const IntegerRegister &value);
        IndirectDecrementOperand(const IndirectDecrementOperand &&other);

        OperandPtr clone()const;
        IntegerRegister countArgument(CorePtr &core,  const IntegerRegister &instruction_PC)const;
    };

    class IndirectIncrementOperand: public Operand
    {
    public:
        IndirectIncrementOperand(const IndirectIncrementOperand &other);
        explicit IndirectIncrementOperand(const IntegerRegister &value);
        IndirectIncrementOperand(const IndirectIncrementOperand &&other);

        OperandPtr clone()const;
        IntegerRegister countArgument(CorePtr &core,  const IntegerRegister &instruction_PC)const;
    };

}

#endif // REALOPERANDS_HPP

