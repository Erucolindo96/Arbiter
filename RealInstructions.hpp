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

    class ADDInstruction: public Instruction
    {
    public:
        explicit ADDInstruction();
        ADDInstruction(const ADDInstruction &other);
        explicit ADDInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        ADDInstruction& operator=(const ADDInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~ADDInstruction();

    };

    class SUBInstruction: public Instruction
    {
    public:
        explicit SUBInstruction();
        SUBInstruction(const SUBInstruction &other);
        explicit SUBInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        SUBInstruction& operator=(const SUBInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~SUBInstruction();

    };

    class JMPInstruction: public Instruction
    {
    public:
        explicit JMPInstruction();
        JMPInstruction(const JMPInstruction &other);
        explicit JMPInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        JMPInstruction& operator=(const JMPInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~JMPInstruction();

    };

    class JMZInstruction: public Instruction
    {
    public:
        explicit JMZInstruction();
        JMZInstruction(const JMZInstruction &other);
        explicit JMZInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        JMZInstruction& operator=(const JMZInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~JMZInstruction();

    };

    class JMNInstruction: public Instruction
    {
    public:
        explicit JMNInstruction();
        JMNInstruction(const JMNInstruction &other);
        explicit JMNInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        JMNInstruction& operator=(const JMNInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~JMNInstruction();

    };

    class DJNInstruction: public Instruction
    {
    public:
        explicit DJNInstruction();
        DJNInstruction(const DJNInstruction &other);
        explicit DJNInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        DJNInstruction& operator=(const DJNInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~DJNInstruction();

    };

    class CMPInstruction: public Instruction
    {
    public:
        explicit CMPInstruction();
        CMPInstruction(const CMPInstruction &other);
        explicit CMPInstruction(const OperandPtr &operand_A, const OperandPtr &operand_B);

        CMPInstruction& operator=(const CMPInstruction& other);

        virtual ExecutionLog execute(CorePtr &core, const IntegerRegister &instruction_PC) ;
        virtual Instruction::InsPtr clone()const;

        virtual ~CMPInstruction();

    };

}




#endif // REALINSTRUCTIONS_HPP

