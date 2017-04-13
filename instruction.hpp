#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP


#include"operand.hpp"

namespace arbiter
{

class Instruction
{
public:
    Instruction(const Instruction& other);
    Instruction(const Opcode op_code, const Operand& operand_A, const Operand& operand_B);
    Instruction& operator=(const Instruction& other);

    Operand operandA() const;
    Operand operandB() const;
    void setOperandA(const Operand& operand);
    void setOperandB(const Operand& operand);

    Opcode instructionType() const ;
    void setInstructionType(const Opcode op_code);


    ~Instruction();//chyba nie bedzie trzeba dziedziczyć po tym - w dodatku chyba niepotrzebny

private:

    Operand _operand_A;
    Operand _operand_B;
    Opcode _op_code;

    Instruction();



};
}
#endif // INSTRUCTION_HPP
