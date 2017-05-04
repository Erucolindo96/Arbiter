#include "Operand.hpp"
namespace arbiter
{

    typedef std::shared_ptr<Core> CorePtr;

    //public
    Operand::Operand(IntegerRegister value ): value_(value)
    {}

    Operand::Operand(const Operand& other): value_(other.value_)
    {}

    Operand::Operand(const Operand &&other):  value_(other.value_)
    {}

    Operand& Operand::operator=(const Operand& other)
    {
        if(this == &other)
            return *this;

        value_ = other.value_;
        return *this;
    }

    Operand& Operand::operator=(const Operand &&other)
    {
        if(this == &other)
            return *this;

        value_ = other.value_;
        return *this;
    }

    IntegerRegister Operand::getValue()const
    {
        return value_;
    }

    void Operand::setValue(const IntegerRegister value)
    {
        value_ = value;
    }





    //protected

}
