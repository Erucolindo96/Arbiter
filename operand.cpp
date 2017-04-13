#include "operand.hpp"
namespace arbiter
{

//public

Operand::Operand(const Operand &other) : _op_type(other._op_type), _value(other._value)
{}


Operand::Operand(AdressingType op_type, int value) : _op_type(op_type), _value(value)
{}

Operand& Operand::operator=(const Operand& other)
{
    if(this == &other)
        return *this;
    _value = other._value;
    _op_type = other._op_type;
    return *this;
}

int Operand::getValue()
{
    return _value;
}
void Operand::setValue(int value)
{
    _value = value;
}

AdressingType Operand::getOperantType()
{
    return _op_type;
}
void Operand::setAdressingType(AdressingType op_type)
{
    _op_type = op_type;
}


//private

Operand::Operand() : _op_type(), _value(0)
{}


}
