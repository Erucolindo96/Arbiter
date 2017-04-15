#include "RealInstructions.hpp"
#include <stdexcept>

namespace arbiter
{

    //DAT
    void InstructionDAT::checkAddressingType(Operand op_a)
    {
        if(op_a.getOperantType() != IMMIDIATE || op_a.getOperantType() != INDIRECT_DECREMENT)
            throw std::invalid_argument("Bad argument in DAT instruction");
    }

    InstructionDAT::InstructionDAT()
    {
        operand_A_.setAdressingType(IMMIDIATE);
        operand_A_.setValue(0);

        operand_B_.setAdressingType(IMMIDIATE);
        operand_B_.setValue(0);
    }

    InstructionDAT::InstructionDAT(const InstructionDAT &other): Instruction(other)
    {}

    InstructionDAT::InstructionDAT(const Operand &operand_A, const Operand &operand_B): Instruction(operand_A, operand_B)
    {
        checkAddressingType(operand_A_);
        checkAddressingType(operand_B_);
    }

    Opcode InstructionDAT::getOpcode()
    {
        return DAT;
    }


    //MOV
    void InstructionMOV::checkAddressingType(Operand op_a)
    {
        if(op_a.getOperantType() == IMMIDIATE || op_a.getOperantType() != NULL)
            throw std::invalid_argument("Bad argument in DAT instruction");
    }

    InstructionDAT::InstructionDAT()
    {
        operand_A_.setAdressingType(IMMIDIATE);
        operand_A_.setValue(0);

        operand_B_.setAdressingType(IMMIDIATE);
        operand_B_.setValue(0);
    }

    InstructionDAT::InstructionDAT(const InstructionDAT &other): Instruction(other)
    {}

    InstructionDAT::InstructionDAT(const Operand &operand_A, const Operand &operand_B): Instruction(operand_A, operand_B)
    {
        checkAddressingType(operand_A_);
        checkAddressingType(operand_B_);
    }

    Opcode InstructionDAT::getOpcode()
    {
        return DAT;
    }

}
