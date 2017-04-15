#ifndef OPERAND_HPP
#define OPERAND_HPP


namespace arbiter
{


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
        INDIRECT_INCREMENT,
        NULL
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

    AdressingType op_type_;
    int value_;
    Operand();

};

}
#endif // OPERAND_HPP
