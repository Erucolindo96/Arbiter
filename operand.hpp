#ifndef OPERAND_HPP
#define OPERAND_HPP


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


/**
 * @brief The AdressingType enum
 * Represent type of adressing
 *
 *
 *
 */

typedef enum AdressingType
{
        IMMIDIATE,
        DIRECT,
        INDIRECT,
        INDIRECT_DECREMENT,
        INDIRECT_INCREMENT
}AdressingType;



class Operand
{
public:


    Operand(AdressingType op_type, int value);
    Operand(const Operand& other);
    Operand& operator=(const Operand& other);

    int getValue();
    void setValue(int value);
    AdressingType getOperantType();
    void setAdressingType(AdressingType op_type);



protected:

    AdressingType _op_type;
    int _value;
    Operand();

};
}
#endif // OPERAND_HPP
