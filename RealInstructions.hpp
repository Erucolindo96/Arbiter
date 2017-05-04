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


    class DATInstruction: public Instruction
    {
        //typedef std::unique_ptr<Operand> OperandPtr;
       // typedef std::shared_ptr<Instruction> InsPtr;

        explicit DATInstruction();
        explicit DATInstruction(const OperandPtr operand_A, const OperandPtr operand_B);
        DATInstruction(const DATInstruction& other);
        //to chyba tak nie dziala
        //wszystkie dozwolone konstruktowy dla tej instrukcji - tylko operand natychmiastowy i posredni zmniejszany
        //explicit DATInstruction(const ImmidOperandPtr operand_A, const ImmidOperandPtr operand_B);
        //explicit DATInstruction(const DecrementOperandPtr operand_A, const DecrementOperandPtr operand_B);
        //explicit DATInstruction(const DecrementOperandPtr operand_A, const ImmidOperandPtr operand_B);
        //explicit DATInstruction(const ImmidOperandPtr operand_A, const DecrementOperandPtr operand_B);

        //DATInstruction& operator=(const DATInstruction& other);

        virtual ExecutionLog execute(CorePtr core) ;
        virtual InsPtr clone()const;

        virtual ~DATInstruction();

    };
    class MOVInstruction: public Instruction
    {
        explicit MOVInstruction();
        //to chyba tak nie dziala
        //wszystkie dozwolone konstruktowy dla tej instrukcji - argument A moze byc dowolny, argument B nie moze byc natychmiastowy
        //explicit MOVInstruction(const OperandPtr operand_A, const DirectOperandPtr operand_B);
        //explicit MOVInstruction(const OperandPtr operand_A, const IndirectOperandPtr operand_B);
        //explicit MOVInstruction(const OperandPtr operand_A, const DecrementOperandPtr operand_B);
        //explicit MOVInstruction(const OperandPtr operand_A, const IncrementOperandPtr operand_B);

        MOVInstruction& operator=(const MOVInstruction& other);

        virtual ExecutionLog execute(CorePtr core) ;
        virtual std::unique_ptr<Instruction> clone()const;

        virtual ~MOVInstruction();


    };
}




#endif // REALINSTRUCTIONS_HPP
