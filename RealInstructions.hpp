#ifndef REALINSTRUCTIONS_HPP
#define REALINSTRUCTIONS_HPP

#include"Instruction.hpp"
#include <memory>
#include"RealOperands.hpp"
namespace arbiter
{

    //typedef std::unique_ptr<ImmidiateOperand> ImmidOperandPtr;
    //typedef std::unique_ptr<DirectOperand> DirectOperandPtr;
    //typedef std::unique_ptr<IndirectOperand> IndirectOperandPtr;
    //typedef std::unique_ptr<IndirectDecrementOperand> DecrementOperandPtr;
    //typedef std::unique_ptr<IndirectIncrementOperand> IncrementOperandPtr;
    class Instruction;

    class DATInstruction: public Instruction
    {

    public:
        explicit DATInstruction();
        DATInstruction(const DATInstruction& other);
        explicit DATInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);


        virtual DATInstruction& operator=(const DATInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC);
        virtual InsPtr clone()const;

        virtual ~DATInstruction();

    };
    class MOVInstruction: public Instruction
    {
    public:
        explicit MOVInstruction();
        MOVInstruction(const MOVInstruction &other);
        explicit MOVInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        MOVInstruction& operator=(const MOVInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~MOVInstruction();


    };
}




#endif // REALINSTRUCTIONS_HPP

