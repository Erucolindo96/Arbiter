#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP


#include"Operand.hpp"

namespace arbiter
{

/**
  @class Operand

  Class Operand represent an Operand of istruction Red Code Assembler


  */


typedef enum Opcode
{
DAT,
MOV,
ADD,
SUB,
JMP,
JMZ,
JMN,
DJN,
CMP,
SPL,
SLT
} Opcode;



class Instruction
{
public:

    explicit Instruction();
    explicit Instruction(const Instruction& other);
    explicit Instruction(const Operand& operand_A, const Operand& operand_B);
    Instruction& operator=(const Instruction& other) ;

    Operand operandA() const;
    Operand operandB() const;
    void setOperandA(const Operand& operand);
    void setOperandB(const Operand& operand);

    virtual Opcode getOpcode() = 0 ;

    virtual ~Instruction();//chyba nie bedzie trzeba dziedziczyć po tym - w dodatku chyba niepotrzebny

protected:

    Operand operand_A_;
    Operand operand_B_;
    virtual void checkAddressingType(Operand op) = 0 ;//rzuca wyjątek gdy złe typy adresowania



};
}
#endif // INSTRUCTION_HPP
