#ifndef INSTRUCTIONDAT_HPP
#define INSTRUCTIONDAT_HPP

#include "Instruction.hpp"
#include "Operand.hpp"
namespace arbiter
{

    class InstructionDAT : public Instruction
    {
    public:
        InstructionDAT();
        InstructionDAT(const InstructionDAT &other);
        InstructionDAT(const Operand& operand_A, const Operand& operand_B);

        virtual Opcode getOpcode();
    protected:
        virtual void checkAddressingType(Operand op_a);
    };


    class InstructionMOV : public Instruction
    {
    public:
        InstructionMOV();
        InstructionMOV(const InstructionMOV &other);
        InstructionMOV(const Operand& operand_A, const Operand& operand_B);

        virtual Opcode getOpcode();
    protected:
        virtual void checkAddressingType(Operand op_a);
    };

/*
    class InstructionMOV : public Instruction
    {
    public:
        InstructionMOV(const InstructionMOV &other);
        InstructionMOV(const Operand& operand_A, const Operand& operand_B);

        virtual Opcode getOpcode();
    protected:
        InstructionMOV() = delete;
        virtual void checkAddressingType(Operand op_a);
    };

    class InstructionMOV : public arbiter::Instruction
    {
    public:
        explicit InstructionMOV();
        InstructionMOV(const InstructionMOV &other);
        InstructionMOV(const Operand& operand_A, const Operand& operand_B);
        InstructionMOV& operator=(const InstructionMOV& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionADD : public arbiter::Instruction
    {
    public:
        InstructionADD();
        InstructionADD(const InstructionADD &other);
        InstructionADD(const Operand& operand_A, const Operand& operand_B);
        InstructionADD& operator=(const InstructionADD& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionSUB : public arbiter::Instruction
    {
    public:
        InstructionSUB();
        InstructionSUB(const InstructionSUB &other);
        InstructionSUB(const Operand& operand_A, const Operand& operand_B);
        InstructionSUB& operator=(const InstructionSUB& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionJMP : public arbiter::Instruction
    {
    public:
        InstructionJMP();
        InstructionJMP(const InstructionJMP &other);
        InstructionJMP(const Operand& operand_A, const Operand& operand_B);//przedefiniować, aby zabezpieczyć przed zlymi danymi
        InstructionJMP& operator=(const InstructionJMP& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionJMZ : public arbiter::Instruction
    {
    public:
        InstructionJMZ();
        InstructionJMZ(const InstructionJMZ &other);
        InstructionJMZ(const Operand& operand_A, const Operand& operand_B);
        InstructionJMZ& operator=(const InstructionJMZ& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionJMN : public arbiter::Instruction
    {
    public:
        InstructionJMN();
        InstructionJMN(const InstructionJMN &other);
        InstructionJMN(const Operand& operand_A, const Operand& operand_B);
        InstructionJMN& operator=(const InstructionJMN& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionDJN : public arbiter::Instruction
    {
    public:
        InstructionDJN();
        InstructionDJN(const InstructionDJN &other);
        InstructionDJN(const Operand& operand_A, const Operand& operand_B);
        InstructionDJN& operator=(const InstructionDJN& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionCMP : public arbiter::Instruction
    {
    public:
        InstructionCMP();
        InstructionCMP(const InstructionCMP &other);
        InstructionCMP(const Operand& operand_A, const Operand& operand_B);
        InstructionCMP& operator=(const InstructionCMP& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };

    class InstructionSPL : public arbiter::Instruction
    {
    public:
        InstructionSPL();
        InstructionSPL(const InstructionSPL &other);
        InstructionSPL(const Operand& operand_A, const Operand& operand_B);
        InstructionSPL& operator=(const InstructionSPL& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };


    class InstructionSLT : public arbiter::Instruction
    {
    public:
        InstructionSLT();
        InstructionSLT(const InstructionSLT &other);
        InstructionSLT(const Operand& operand_A, const Operand& operand_B);
        InstructionSLT& operator=(const InstructionSLT& other);

        void setOperandA(const Operand& operand);//nalezy je przedefiniować, by zabezpieczyć przed złymi danymi
        void setOperandB(const Operand& operand);

        virtual Opcode getOpcode();
    };
*/
}

#endif // INSTRUCTIONDAT_HPP
