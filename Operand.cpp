#include "Operand.hpp"
namespace arbiter
{

//public

Operand::Operand(const Operand &other) : op_type_(other.op_type_), value_(other.value_)
{}


Operand::Operand(AdressingType op_type, int value) : op_type_(op_type), value_(value)
{}

Operand& Operand::operator=(const Operand& other)
{
    if(this == &other)
        return *this;
    value_ = other.value_;
    op_type_ = other.op_type_;
    return *this;
}

int Operand::getValue()
{
    return value_;
}
void Operand::setValue(int value)
{
    value_ = value;
}

AdressingType Operand::getOperantType()
{
    return op_type_;
}
void Operand::setAdressingType(AdressingType op_type)
{
    op_type_ = op_type;
}


//private

Operand::Operand() : op_type_(), value_(0)
{}


}
